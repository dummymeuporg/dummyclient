#include <iostream>
#include <cstdlib>
#include <cstring>

#include "client.hpp"
#include "credentials.hpp"

#include "client_state/initial_state.hpp"
#include "client_state/receive_characters_state.hpp"

namespace ClientState {

InitialState::InitialState(::Client& client) : State(client) {}

void InitialState::resume() {
    const ::Credentials& creds(m_client.credentials());
    const std::string& account(creds.account());
    const std::uint8_t* sessionID(creds.sessionID());

    std::array<std::uint8_t, 16> sessionIDArray;

    std::copy(sessionID, sessionID + 16, sessionIDArray.data());

    Dummy::Protocol::OutgoingPacket pkt;
    pkt << account << sessionIDArray;

    // Send the packet.
    m_client.send(pkt);

}

void InitialState::onRead(Dummy::Protocol::IncomingPacket& pkt) {
    auto self(shared_from_this());
    std::cerr << "Will read data." << std::endl;
    std::uint8_t status;
    pkt >> status;
    if (status == 1) {
        std::cerr << "Login successfull!" << std::endl;
        m_client.changeState(
            std::make_shared<ClientState::ReceiveCharactersState>(m_client)
        );
    } else {
        std::cerr << "wrong credentials." << std::endl;
        ::exit(-1);
    }
}

} // namespace ClientState

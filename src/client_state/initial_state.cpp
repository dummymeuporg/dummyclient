#include <iostream>
#include <cstdlib>
#include <cstring>

#include "client.hpp"
#include "credentials.hpp"

#include "client_state/initial_state.hpp"
#include "client_state/receive_characters_state.hpp"

#include "server/command/connect_command.hpp"

namespace ClientState {

InitialState::InitialState(::Client& client) : State(client) {}

void InitialState::resume() {
    /*
    const ::Credentials& creds(m_client.credentials());
    const std::string& account(creds.account());
    const std::string sessionID(creds.sessionID());

    Dummy::Protocol::OutgoingPacket pkt;
    pkt << account << sessionID;

    // Send the packet.
    m_client.send(pkt);
    */
    Dummy::Server::Command::ConnectCommand cmd(
        m_client.credentials().account(),
        m_client.credentials().sessionID()
    );
    m_client.sendCommand(cmd);
}

void InitialState::onRead(Dummy::Protocol::IncomingPacket& pkt) {
    /*
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
    */
}


void
InitialState::onResponse(const Dummy::Server::Response::Response& response) {
    auto self(shared_from_this());
    std::cerr << "GOT RESPONSE! status = "
        << static_cast<int>(response.status()) << std::endl;
    switch(response.status()) {
    case 0: /* O.K. */
        /*
        m_client.changeState(
            std::make_shared<ClientState::ReceiveCharactersState>(m_client)
        );
        */
        break;
    default: /* N.O.K. */
        break;
    }
}

} // namespace ClientState

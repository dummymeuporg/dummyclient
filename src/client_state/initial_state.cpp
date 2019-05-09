#include <iostream>
#include <cstdlib>
#include <cstring>

#include "client.hpp"
#include "credentials.hpp"

#include "client_state/initial_state.hpp"

namespace ClientState {

InitialState::InitialState(::Client& client) : State(client) {}

void InitialState::resume() {
    const ::Credentials& creds(m_client.credentials());
    const std::string& account(creds.account());
    const std::uint8_t* sessionID(creds.sessionID());

    std::vector<std::uint8_t> buffer(
        sizeof(std::uint16_t) + // holds the size of the packet
        sizeof(std::uint16_t) + // holds the size of the account name
        account.size() + // holds the account
        16 // holds the uuid.
    );
    *(reinterpret_cast<std::uint16_t*>(buffer.data())) =
        buffer.size() - sizeof(std::uint16_t);
    *(reinterpret_cast<std::uint16_t*>(buffer.data()) + 1) =
        account.size();

    // Put the account
    std::copy(account.begin(),
              account.end(),
              buffer.data() + 2 * sizeof(std::uint16_t)
    );

    // Put the session ID
    ::memcpy(buffer.data() + (2 * sizeof(std::uint16_t) + account.size()),
             sessionID,
             16);

    // Send the packet.
    m_client.socket().send(buffer.data(), buffer.size());

}

void InitialState::onRead(const std::vector<std::uint8_t>& buffer) {
    if (buffer[0] == 1) {
        std::cerr << "Login successfull!" << std::endl;
    } else {
        std::cerr << "wrong credentials." << std::endl;
        ::exit(-1);
    }
}

} // namespace ClientState

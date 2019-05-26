#include <iostream>

#include "client.hpp"
#include "game.hpp"

#include "client_state/loading_state.hpp"

namespace ClientState {

LoadingState::LoadingState(::Client& client)
    : State(client)
{

}

void LoadingState::resume() {
    // What do we do?
}

void LoadingState::onRead(Dummy::Protocol::IncomingPacket& pkt) {
    std::cerr << "[LoadingState]" << std::endl;
    std::uint8_t answer;
    pkt >> answer;
    switch(answer) {
    case 1:
        break;
    default:
        break;
    }
}

} // namespace ClienState

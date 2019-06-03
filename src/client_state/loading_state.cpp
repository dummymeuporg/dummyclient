#include <iostream>

#include "client.hpp"
#include "game.hpp"

#include "client_state/loading_state.hpp"
#include "client_state/playing_state.hpp"

namespace ClientState {

LoadingState::LoadingState(::Client& client)
    : State(client), m_model(std::make_shared<Model::LoadingModel>())
{

}

void LoadingState::resume() {
    std::cerr << "[LoadingState]" << std::endl;
    // What do we do?
}

void LoadingState::onRead(Dummy::Protocol::IncomingPacket& pkt) {
    std::cerr << "[LoadingState]" << std::endl;
    std::uint8_t answer;
    pkt >> answer;
    switch(answer) {
    case 1:
        std::cerr << "Good for teleporting" << std::endl;
        m_model->setStatus(1);
        m_model->visit(
            std::reinterpret_pointer_cast<Screen::LoadingScreen>(
                m_client.game().screen()
            )
        );
        /*
         * XXX: Do not change the state here, unfortunately.
        m_client.changeState(
            std::make_shared<PlayingState>(m_client)
        );
        */
        break;
    default:
        break;
    }
}

} // namespace ClienState

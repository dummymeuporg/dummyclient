#include <iostream>

#include "client.hpp"
#include "game.hpp"
#include "client_state/receive_characters_state.hpp"
#include "model/characters_list_model.hpp"

namespace ClientState {

ReceiveCharactersState::ReceiveCharactersState(::Client& client)
    : State(client)
{
}

void ReceiveCharactersState::resume() {
    // Nothing to do for now.
    // The client will select the character later on.
    m_model = std::make_shared<Model::CharactersListModel>();
    m_client.game().screen()->setModel(m_model);
}

void ReceiveCharactersState::onRead(const std::vector<std::uint8_t>& buffer) {
    // Here, we will get the server answer once the character has been either
    // created or selected.
    std::uint16_t charactersCount =
        *(reinterpret_cast<const std::uint16_t*>(buffer.data()));
    std::cerr << "[ReceiveCharactersState] got " << charactersCount <<
        " characters. " << std::endl;

    m_model->update();
}

} // namespace ClientState

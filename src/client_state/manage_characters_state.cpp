#include <iostream>

#include "client.hpp"
#include "game.hpp"
#include "client_state/manage_characters_state.hpp"
#include "model/characters_list_model.hpp"

namespace ClientState {

ManageCharactersState::ManageCharactersState(::Client& client)
    : State(client)
{
}

void ManageCharactersState::resume() {
    m_model = std::make_shared<Model::CharactersListModel>();
    m_client.game().screen()->setModel(m_model);
}

void ManageCharactersState::onRead(Dummy::Protocol::IncomingPacket& pkt) {
    std::uint8_t answer;
    pkt >> answer;
    if (answer) {
        // The character has been successfully created.
        // Read its info and add it to the list.
        std::shared_ptr<Dummy::Core::Character> chr =
            std::make_shared<Dummy::Core::Character>();
        pkt >> *chr;
        m_model->addCharacter(chr);
        m_model->update();
    }
}

} // namespace ClientState

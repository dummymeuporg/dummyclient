#include <memory>
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
    // So ugly.
    m_model = std::dynamic_pointer_cast<Model::CharactersListModel>(
        m_client.game().screen()->model()
    );
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
    }
}

} // namespace ClientState

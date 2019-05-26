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
    std::shared_ptr<Dummy::Core::Character> chr = nullptr;
    switch (answer) {
    case 1:
        // The character has been successfully created.
        // Read its info and add it to the list.
        chr = std::make_shared<Dummy::Core::Character>();
        pkt >> *chr;
        m_model->addCharacter(chr);
        break;
    case 2:
        // The character has been selected.
        break;
    default:
        // Something went wrong.
        break;
    }
}

} // namespace ClientState

#include <memory>
#include <iostream>

#include "client.hpp"
#include "game.hpp"
#include "client_state/loading_state.hpp"
#include "client_state/manage_characters_state.hpp"
#include "model/characters_list_model.hpp"

namespace ClientState {

ManageCharactersState::ManageCharactersState(
    ::Client& client, std::shared_ptr<Model::CharactersListModel> model)
    : State(client), m_model(model)
{
}

void ManageCharactersState::resume() {
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
        // XXX: ugly.
        m_model->visit(
            std::reinterpret_pointer_cast<Screen::CreateCharacterScreen>(
                m_client.game().screen()
            )
        );
        break;
    case 2:
        // The character has been selected. Switch to loading state.
        m_client.changeState(
            std::make_shared<LoadingState>(m_client)
        );
        break;
    default:
        // Something went wrong.
        break;
    }
}

} // namespace ClientState

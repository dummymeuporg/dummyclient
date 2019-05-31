#include <iostream>

#include <boost/range/irange.hpp>

#include "graphics/living.hpp"

#include "model/playing_model.hpp"

#include "protocol/character_position.hpp"
#include "protocol/character_off.hpp"
#include "protocol/map_update_manager.hpp"

#include "client.hpp"
#include "game.hpp"

#include "client_state/playing_state.hpp"

using UpdateCode = Dummy::Protocol::MapUpdateManager::Code;

namespace ClientState {

PlayingState::PlayingState(::Client& client)
    : State(client), m_model(nullptr)
{}

void PlayingState::resume() {
    std::cerr << "[PlayingState]" << std::endl;
    // XXX: still ugly.
    m_model = std::dynamic_pointer_cast<Model::PlayingModel>(
        m_client.game().screen()->model()
    );
    std::cerr << "model = " << m_model << std::endl;
}

void PlayingState::onRead(Dummy::Protocol::IncomingPacket& pkt) {
    //std::cerr << "Read playing state." << std::endl;
    std::uint8_t answer;
    pkt >> answer;
    switch(answer) {
    case 1: /* O.K. */
        _parseMapUpdates(pkt);
        break;
    default: /* N.O.K. */
        break;
    }
}

void PlayingState::_parseMapUpdates(Dummy::Protocol::IncomingPacket& pkt) {
    std::uint16_t count;
    pkt >> count;
    //std::cerr << "Map updates count: " << count << std::endl;
    for (const auto& i: boost::irange(count)) {
        UpdateCode c;
        pkt >> reinterpret_cast<std::uint16_t&>(c);
        //std::cerr << "Code: " << static_cast<int>(c) << std::endl;
        switch(c) {
        case UpdateCode::CHARACTER_POSITION:
            _handleCharacterPosition(pkt);
            m_model->update();
            break;
        case UpdateCode::CHARACTER_OFF:
            _handleCharacterOff(pkt);
            m_model->update();
            break;
        default:
            // XXX: error?
            break;
        }
    }
}

void
PlayingState::_handleCharacterPosition(Dummy::Protocol::IncomingPacket& pkt) {
    std::uint16_t x, y;
    std::string name;
    std::string chipset;
    Dummy::Core::Character::Direction direction;

    //std::cerr << "Character position." << std::endl;

    // Read info
    pkt >> x >> y >> name >> chipset 
        >> reinterpret_cast<std::uint8_t&>(direction);

    std::shared_ptr<Dummy::Protocol::CharacterPosition> pos =
        std::make_shared<Dummy::Protocol::CharacterPosition>(
            x, y, name, chipset, direction
        );

    // Check if the character is in the livings
    std::shared_ptr<Graphics::Living> living(nullptr);
    if (m_model->livings().find(name) == std::end(m_model->livings())) {
        // Not found? Add it.
        living =
            std::make_shared<Graphics::Living>(
                chipset, name, 24, 32, x, y, direction
            );
        m_model->addLiving(name, living);
        //std::cerr << "Added living " << name << std::endl;
    } else {
        living = m_model->getLiving(name);
        //std::cerr << "Found living " << name << std::endl;

        // Update living info.
        living->setPosition(x, y);
        living->setDirection(direction);
        living->setChipsetName(chipset);
    }
}

void PlayingState::_handleCharacterOff(Dummy::Protocol::IncomingPacket& pkt) {
    std::string name;

    pkt >> name;

    if (m_model->livings().find(name) != std::end(m_model->livings())) {
        std::cerr << "Remove living " << name << std::endl;
        m_model->removeLiving(name);
    }
    
}

}

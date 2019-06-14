#include "protocol/map_update/character_off.hpp"
#include "protocol/map_update/character_on.hpp"
#include "protocol/map_update/character_position.hpp"
#include "graphics/living.hpp"
#include "local_map_state.hpp"

LocalMapState::LocalMapState() {}

void LocalMapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::CharacterPosition& characterPosition
) {
    Dummy::Server::MapState::visitMapUpdate(characterPosition);
    const std::string& name(characterPosition.name());
    int xVector, yVector;
    if (livings().find(name) != std::end(livings())) {
        const auto& modelLiving(living(name));

    }
}


void LocalMapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::CharacterOn& characterOn
) {

}


void LocalMapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::CharacterOff& characterOff
) {

}

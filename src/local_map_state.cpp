#include <set>

#include <dummy/protocol/map_update/named_living_off.hpp>
#include <dummy/protocol/map_update/named_living_on.hpp>
#include <dummy/protocol/map_update/character_position.hpp>
#include <dummy/protocol/living.hpp>

#include "graphics/foe_player.hpp"
#include "local_map_state.hpp"
#include "map_view.hpp"

LocalMapState::LocalMapState(const MapView& mapView)
    : m_mapView(mapView)
{
    // Instantiate floor states.
    for (const auto& floor: m_mapView.floorViews()) {
        m_localFloorStates.push_back(LocalFloorState(*this));
    }
}

void LocalMapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::CharacterPosition& characterPosition
) {
    Dummy::Server::MapState::visitMapUpdate(characterPosition);
    // Get the character's floor.
    const auto& floor(m_graphicFoesFloor[characterPosition.name()]);
    m_localFloorStates[floor].onCharacterPosition(characterPosition);
}


void LocalMapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::LivingOn& namedLivingOn
) {
    Dummy::Server::MapState::visitMapUpdate(namedLivingOn);

    // Check that its floor is valid.
    const auto& floor(namedLivingOn.floor());

    if (floor >= m_mapView.floorViews().size()) {
        // XXX: throw exception?
    }

    auto& localFloorState(m_localFloorStates[floor]);

    if (localFloorState.containsLiving(namedLivingOn.name())) {
        // XXX: throw exception?
    }

    auto foe = std::make_shared<Graphics::FoePlayer>(
        m_mapView,
        namedLivingOn.chipset(),
        namedLivingOn.name(),
        8 * namedLivingOn.x(),
        8 * namedLivingOn.y(),
        namedLivingOn.floor(),
        m_mapView.scaleFactor(),
        namedLivingOn.direction()
    );

    localFloorState.addFoe(namedLivingOn.name(), foe);
    m_graphicFoesFloor[namedLivingOn.name()] = floor;
}

void LocalMapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::LivingOff& namedLivingOff
) {
    Dummy::Server::MapState::visitMapUpdate(namedLivingOff);

    // Get the appropriate floor and dispatch.
    const auto& floor(m_graphicFoesFloor[namedLivingOff.name()]);
    m_localFloorStates[floor].removeFoe(namedLivingOff.name());
}

void LocalMapState::tick() {
    for (auto& floorState: m_localFloorStates) {
        floorState.tick();
    }
}

void LocalMapState::say(const std::string& author, const std::string& message)
{
    // Get the floor and dispatch.
    const auto& floor(m_graphicFoesFloor[author]);
    m_localFloorStates[floor].say(author, message);
}

#include <set>

#include <dummy/protocol/map_update/living_on.hpp>
#include <dummy/protocol/map_update/living_off.hpp>
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
    const auto& floor(m_graphicFoesFloor[characterPosition.id()]);
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

    if (localFloorState.containsLiving(namedLivingOn.id())) {
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

    localFloorState.addFoe(namedLivingOn.id(), foe);
    m_graphicFoesFloor[namedLivingOn.id()] = floor;
}

void LocalMapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::LivingOff& livingOff
) {
    Dummy::Server::MapState::visitMapUpdate(livingOff);

    // Get the appropriate floor and dispatch.
    const auto& floor(m_graphicFoesFloor[livingOff.id()]);
    m_localFloorStates[floor].removeFoe(livingOff.id());
}

void LocalMapState::tick() {
    for (auto& floorState: m_localFloorStates) {
        floorState.tick();
    }
}

void LocalMapState::say(std::uint32_t id, const std::string& message)
{
    // Get the floor and dispatch.
    const auto& floor(m_graphicFoesFloor[id]);
    m_localFloorStates[floor].say(id, message);
}

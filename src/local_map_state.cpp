#include <set>

#include "protocol/map_update/character_off.hpp"
#include "protocol/map_update/character_on.hpp"
#include "protocol/map_update/character_position.hpp"
#include "protocol/living.hpp"
#include "graphics/living.hpp"
#include "local_map_state.hpp"
#include "map_view.hpp"

LocalMapState::LocalMapState(const MapView& mapView)
    : m_mapView(mapView)
{
    // Instantiate floor states.
    for (const auto& floor: m_mapView.levelViews()) {
        m_localFloorStates.push_back(LocalFloorState(*this));
    }
}

void LocalMapState::setIdleLivings() {
    /*
    for (const auto& living: m_graphicLivingsMap) {
        m_idleLivings.insert(living.first);
    }
    */
}

void LocalMapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::CharacterPosition& characterPosition
) {
    /*
    std::cerr << "[!] " <<
        characterPosition.name() << " IS AT " <<
        characterPosition.x() << ", " <<
        characterPosition.y() << std::endl;

    Dummy::Server::MapState::visitMapUpdate(characterPosition);
    const std::string& name(characterPosition.name());
    int xVector = 0, yVector = 0;
    if (livings().find(name) != std::end(livings()) &&
        m_graphicLivingsMap.find(name) != std::end(m_graphicLivingsMap))
    {
        const auto& modelLiving(living(name)); 
        auto& graphicLiving(*m_graphicLivingsMap.at(name));
        auto scaleFactor(graphicLiving.scaleFactor());
        auto modelLivingX(modelLiving.x() * 8 * scaleFactor);
        auto modelLivingY(modelLiving.y() * 8 * scaleFactor);
        if (modelLivingX != graphicLiving.x()) {
            graphicLiving.setXMovement(
                2 * (graphicLiving.x() < modelLivingX) - 1
            );
        }
        if (modelLivingY != graphicLiving.y()) {
            graphicLiving.setYMovement(
                2 * (graphicLiving.y() < modelLivingY) - 1
            );
        }
        // XXX: ugly
        graphicLiving.moveTowards(
            modelLiving.x() * 8 * scaleFactor,
            modelLiving.y() * 8 * scaleFactor
        );
        graphicLiving.walk();
        m_idleLivings.erase(name);
    }
    */
}


void LocalMapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::CharacterOn& characterOn
) {
    Dummy::Server::MapState::visitMapUpdate(characterOn);

    // Check that its floor is valid.
    const auto& floor(characterOn.floor());

    if (floor >= m_mapView.levelViews().size()) {
        // XXX: throw exception?
    }

    auto& localFloorState(m_localFloorStates[floor]);

    /*
    m_graphicLivingsMap[characterOn.name()] =
        std::make_unique<Graphics::Living>(
            m_mapView,
            characterOn.chipset(),
            characterOn.name(),
            24,
            32,
            8 * characterOn.x() * m_mapView.scaleFactor(),
            8 * characterOn.y() * m_mapView.scaleFactor(),
            characterOn.floor(),
            m_mapView.scaleFactor(),
            characterOn.direction(),
            10 // velocity
        );
    */
}

void LocalMapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::CharacterOff& characterOff
) {
    Dummy::Server::MapState::visitMapUpdate(characterOff);
    //m_graphicLivingsMap.erase(characterOff.name());
}

void LocalMapState::tick() {
    for (auto& floorState: m_localFloorStates) {
        floorState.tick();
    }
}

void LocalMapState::syncLivings() {
    /*
    for (const auto& name: m_idleLivings) {
        if (m_graphicLivingsMap.find(name) != std::end(m_graphicLivingsMap)) {
            m_graphicLivingsMap[name]->stand();
        }
    }
    m_idleLivings.clear();
    */
}

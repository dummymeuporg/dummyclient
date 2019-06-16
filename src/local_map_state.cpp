#include "protocol/map_update/character_off.hpp"
#include "protocol/map_update/character_on.hpp"
#include "protocol/map_update/character_position.hpp"
#include "protocol/living.hpp"
#include "graphics/living.hpp"
#include "local_map_state.hpp"
#include "map_view.hpp"

LocalMapState::LocalMapState(const MapView& mapView)
    : m_mapView(mapView)
{}

void LocalMapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::CharacterPosition& characterPosition
) {
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
        auto graphicLivingX(graphicLiving.x() / (8 * scaleFactor));
        auto graphicLivingY(graphicLiving.y() / (8 * scaleFactor));
        if (modelLiving.x() != graphicLivingX) {
            graphicLiving.setXMovement(
                2 * (graphicLivingX < modelLiving.x()) - 1
            );
        }
        if (modelLiving.y() != graphicLivingY) {
            graphicLiving.setYMovement(
                2 * (graphicLivingY < modelLiving.y()) - 1
            );
        }
        // XXX: ugly
        graphicLiving.moveTowards(
            modelLiving.x() * 8 * scaleFactor,
            modelLiving.y() * 8 * scaleFactor
        );
    }
}


void LocalMapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::CharacterOn& characterOn
) {
    Dummy::Server::MapState::visitMapUpdate(characterOn);

    m_graphicLivingsMap[characterOn.name()] =
        std::make_unique<Graphics::Living>(
            m_mapView,
            characterOn.chipset(),
            characterOn.name(),
            24,
            32,
            8 * characterOn.x() * m_mapView.scaleFactor(),
            8 * characterOn.y() * m_mapView.scaleFactor(),
            m_mapView.scaleFactor(),
            characterOn.direction(),
            10 /* velocity */
        );
            
}

void LocalMapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::CharacterOff& characterOff
) {
    Dummy::Server::MapState::visitMapUpdate(characterOff);
    m_graphicLivingsMap.erase(characterOff.name());
}

void LocalMapState::tick() {
    // Make graphic livings converge towards their model.
    auto scaleFactor(m_mapView.scaleFactor());
    for (const auto& [name, graphicLiving]: m_graphicLivingsMap) {
        auto& modelLiving(living(name));
        graphicLiving->tick();
        auto graphicLivingX(graphicLiving->x() / (8 * scaleFactor));
        auto graphicLivingY(graphicLiving->y() / (8 * scaleFactor));

        // XXX: ugly
        if (modelLiving.x() != graphicLivingX) {
            graphicLiving->setXMovement(
                2 * (graphicLivingX < modelLiving.x()) - 1
            );
        } else {
            graphicLiving->setXMovement(0);
        }
        if (modelLiving.y() != graphicLivingY) {
            graphicLiving->setYMovement(
                2 * (graphicLivingY < modelLiving.y()) - 1
            );
        } else {
            graphicLiving->setYMovement(0);
        }
        /*
        std::cerr << "Model living: " <<
            modelLiving.x() << ", " <<
            modelLiving.y() << std::endl;
        std::cerr << "Graphic living: " <<
            graphicLiving->x() << ", " <<
            graphicLiving->y() << std::endl;
        */
        graphicLiving->moveTowards(
            modelLiving.x() * 8 * scaleFactor,
            modelLiving.y() * 8 * scaleFactor
        );
    }
}

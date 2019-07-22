#include "protocol/living.hpp"
#include "graphics/living.hpp"

#include "protocol/map_update/character_position.hpp"

#include "local_map_state.hpp"
#include "local_floor_state.hpp"

LocalFloorState::LocalFloorState(const LocalMapState& localMapState)
    : m_localMapState(localMapState) {}

void LocalFloorState::tick() {
    // Make graphic livings converge towards their model.
    auto scaleFactor(m_localMapState.scaleFactor());
    for (const auto& [name, graphicLiving]: m_graphicLivingsMap) {
        auto& modelLiving(m_localMapState.living(name));
        graphicLiving->tick();
        auto modelLivingX(modelLiving.x() * 8 * scaleFactor);
        auto modelLivingY(modelLiving.y() * 8 * scaleFactor);

        // XXX: ugly
        if (modelLivingX != graphicLiving->x()) {
            graphicLiving->setXMovement(
                2 * (graphicLiving->x() < modelLivingX) - 1
            );
        } else {
            graphicLiving->setXMovement(0);
        }
        if (modelLivingY != graphicLiving->y()) {
            graphicLiving->setYMovement(
                2 * (graphicLiving->y() < modelLivingY) - 1
            );
        } else {
            graphicLiving->setYMovement(0);
        }
    }
}

void
LocalFloorState::addLiving(
    const std::string& name,
    std::shared_ptr<Graphics::Living> living
) {
    m_graphicLivingsMap.emplace(name, living);
}

void
LocalFloorState::removeLiving(const std::string& name) {
    m_graphicLivingsMap.erase(name);
}

void LocalFloorState::onCharacterPosition(
    const Dummy::Protocol::MapUpdate::CharacterPosition& characterPosition
) {
    std::cerr << "LocalFloorState::onCharacterPosition" << std::endl;
    const std::string& name(characterPosition.name());
    int xVector = 0, yVector = 0;
    if (m_localMapState.livings().find(name) !=
        std::end(m_localMapState.livings()) &&
        m_graphicLivingsMap.find(name) != std::end(m_graphicLivingsMap))
    {
        const auto& modelLiving(m_localMapState.living(name));
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
}

void LocalFloorState::syncLivings() {
    for (const auto& name: m_idleLivings) {
        if (m_graphicLivingsMap.find(name) != std::end(m_graphicLivingsMap)) {
            m_graphicLivingsMap[name]->stand();
        }
    }
    m_idleLivings.clear();
}

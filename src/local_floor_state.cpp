#include "protocol/living.hpp"
#include "graphics/foe.hpp"

#include "protocol/map_update/character_position.hpp"

#include "local_map_state.hpp"
#include "local_floor_state.hpp"

LocalFloorState::LocalFloorState(const LocalMapState& localMapState)
    : m_localMapState(localMapState) {}

void LocalFloorState::tick() {
    // Make graphic livings converge towards their model.
    auto scaleFactor(m_localMapState.scaleFactor());
    for (const auto& [name, graphicFoe]: m_graphicFoesMap) {
        auto& modelLiving(m_localMapState.foe(name));
        graphicFoe->tick();
        auto modelLivingX(modelLiving.x() * 8 * scaleFactor);
        auto modelLivingY(modelLiving.y() * 8 * scaleFactor);

        // XXX: ugly
        if (modelLivingX != graphicFoe->x()) {
            graphicFoe->setXMovement(
                2 * (graphicFoe->x() < modelLivingX) - 1
            );
        } else {
            graphicFoe->setXMovement(0);
        }
        if (modelLivingY != graphicFoe->y()) {
            graphicFoe->setYMovement(
                2 * (graphicFoe->y() < modelLivingY) - 1
            );
        } else {
            graphicFoe->setYMovement(0);
        }
    }
}

void
LocalFloorState::addFoe(
    const std::string& name,
    std::shared_ptr<Graphics::Foe> living
) {
    m_graphicFoesMap.emplace(name, living);
}

void
LocalFloorState::removeFoe(const std::string& name) {
    m_graphicFoesMap.erase(name);
}

void LocalFloorState::onCharacterPosition(
    const Dummy::Protocol::MapUpdate::CharacterPosition& characterPosition
) {
    std::cerr << "LocalFloorState::onCharacterPosition" << std::endl;
    const std::string& name(characterPosition.name());
    int xVector = 0, yVector = 0;
    if (m_localMapState.livings().find(name) !=
        std::end(m_localMapState.livings()) &&
        m_graphicFoesMap.find(name) != std::end(m_graphicFoesMap))
    {
        const auto& modelFoe(m_localMapState.foe(name));
        auto& graphicFoe(*m_graphicFoesMap.at(name));
        auto scaleFactor(graphicFoe.scaleFactor());
        auto modelFoeX(modelFoe.x() * 8 * scaleFactor);
        auto modelFoeY(modelFoe.y() * 8 * scaleFactor);
        if (modelFoeX != graphicFoe.x()) {
            graphicFoe.setXDst(modelFoeX);
            graphicFoe.setXMovement(
                2 * (graphicFoe.x() < modelFoeX) - 1
            );
        }
        if (modelFoeY != graphicFoe.y()) {
            graphicFoe.setYDst(modelFoeY);
            graphicFoe.setYMovement(
                2 * (graphicFoe.y() < modelFoeY) - 1
            );
        }
        // XXX: ugly
        graphicFoe.moveTowards(
            modelFoe.x() * 8 * scaleFactor,
            modelFoe.y() * 8 * scaleFactor
        );
        std::cerr << "Walk" << std::endl;
        graphicFoe.walk();
        m_idleFoes.erase(name);
    }
}

void LocalFloorState::setIdleLivings() {
    for (const auto& foe: m_graphicFoesMap) {
        m_idleFoes.insert(foe.first);
    }
}

void LocalFloorState::syncLivings() {
    for (const auto& name: m_idleFoes) {
        if (m_graphicFoesMap.find(name) != std::end(m_graphicFoesMap)) {
            std::cerr << "Stand" << std::endl;
            m_graphicFoesMap[name]->stand();
        }
    }
    m_idleFoes.clear();
}

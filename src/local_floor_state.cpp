#include <dummy/protocol/living.hpp>
#include <dummy/protocol/map_update/character_position.hpp>
#include "graphics/foe.hpp"


#include "local_map_state.hpp"
#include "local_floor_state.hpp"

LocalFloorState::LocalFloorState(const LocalMapState& localMapState)
    : m_localMapState(localMapState) {}

void LocalFloorState::tick() {
    // Make graphic livings converge towards their model.
    for (const auto& [id, graphicFoe]: m_graphicFoesMap) {
        auto& modelLiving(m_localMapState.living(id));
        graphicFoe->tick();
        auto modelLivingX(modelLiving.x() * 8);
        auto modelLivingY(modelLiving.y() * 8);

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
    std::uint32_t id,
    std::shared_ptr<Graphics::Foe> living
) {
    m_graphicFoesMap.emplace(id, living);
}

void
LocalFloorState::removeFoe(const std::uint32_t id) {
    m_graphicFoesMap.erase(id);
}

void LocalFloorState::onCharacterPosition(
    const Dummy::Protocol::MapUpdate::CharacterPosition& characterPosition
) {
    std::cerr << "LocalFloorState::onCharacterPosition" << std::endl;
    const auto& id(characterPosition.id());
    int xVector = 0, yVector = 0;
    if (m_localMapState.livings().find(id) !=
        std::end(m_localMapState.livings()) &&
        m_graphicFoesMap.find(id) != std::end(m_graphicFoesMap))
    {

        const auto& modelFoe(m_localMapState.living(id));
        auto& graphicFoe(*m_graphicFoesMap.at(id));
        auto modelFoeX(modelFoe.x() * 8);
        auto modelFoeY(modelFoe.y() * 8);
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
            modelFoe.x() * 8,
            modelFoe.y() * 8
        );
    }
}

void
LocalFloorState::say(std::uint32_t id, const std::string& message) {
    if (m_graphicFoesMap.find(id) != std::end(m_graphicFoesMap)) {
        m_graphicFoesMap[id]->say(message);
    }
}

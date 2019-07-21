#include "protocol/living.hpp"
#include "graphics/living.hpp"

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

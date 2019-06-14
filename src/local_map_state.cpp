#include "protocol/map_update/character_off.hpp"
#include "protocol/map_update/character_on.hpp"
#include "protocol/map_update/character_position.hpp"
#include "protocol/living.hpp"
#include "graphics/living.hpp"
#include "local_map_state.hpp"

LocalMapState::LocalMapState() {}

void LocalMapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::CharacterPosition& characterPosition
) {
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

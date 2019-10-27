#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

#include <dummy/server/map_state.hpp>

#include "map_view.hpp"
#include "local_floor_state.hpp"

namespace Graphics {
class Living;
} // namespace Graphics

using LocalFloorStates = std::vector<LocalFloorState>;
using GraphicLivingFloors =
    std::map<std::uint32_t, std::uint8_t>;

class LocalMapState : public Dummy::Server::MapState {
public:
    LocalMapState(const MapView&);
    void visitMapUpdate(
        const Dummy::Protocol::MapUpdate::CharacterPosition&
    ) override;

    void visitMapUpdate(
        const Dummy::Protocol::MapUpdate::LivingOff&
    ) override;

    void visitMapUpdate(
        const Dummy::Protocol::MapUpdate::LivingOn&
    ) override;

    void tick();

    const LocalFloorStates& localFloorStates() const {
        return m_localFloorStates;
    }

    const LocalFloorState& localFloorState(std::size_t index) const {
        return m_localFloorStates[index];
    }

    int scaleFactor() const {
        return m_mapView.scaleFactor();
    }

    void say(std::uint32_t, const std::string&);

private:
    const MapView& m_mapView;
    LocalFloorStates m_localFloorStates;
    GraphicLivingFloors m_graphicFoesFloor;
};

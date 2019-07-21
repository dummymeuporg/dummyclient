#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

#include "server/map_state.hpp"
#include "local_floor_state.hpp"

namespace Graphics {
class Living;
} // namespace Graphics

using GraphicLivingsMap =
    std::map<std::string, std::unique_ptr<Graphics::Living>>;
using LocalFloorStates = std::vector<LocalFloorState>;


class MapView;

class LocalMapState : public Dummy::Server::MapState {
public:
    LocalMapState(const MapView&);
    void visitMapUpdate(
        const Dummy::Protocol::MapUpdate::CharacterPosition&
    ) override;

    void visitMapUpdate(
        const Dummy::Protocol::MapUpdate::CharacterOff&
    ) override;

    void visitMapUpdate(
        const Dummy::Protocol::MapUpdate::CharacterOn&
    ) override;

    void tick();

    const GraphicLivingsMap& graphicLivings() const {
        return m_graphicLivingsMap;
    }

    const LocalFloorStates& localFloorStates() const {
        return m_localFloorStates;
    }

    void setIdleLivings();
    void syncLivings();
private:
    const MapView& m_mapView;
    GraphicLivingsMap m_graphicLivingsMap;
    LocalFloorStates m_localFloorStates;
    std::set<std::string> m_idleLivings;
};

#pragma once

#include <memory>
#include <map>
#include <set>
#include <string>

class LocalMapState;

namespace Graphics {
class Living;
} // namespace Graphics


using GraphicLivingsMap =
    std::map<std::string, std::unique_ptr<Graphics::Living>>;

class LocalFloorState {
public:
    LocalFloorState(const ::LocalMapState&);
    GraphicLivingsMap& graphicLivings() {
        return m_graphicLivingsMap;
    }

    Graphics::Living& graphicLiving(const std::string& name) {
        return *m_graphicLivingsMap[name];
    }

    void tick();

private:
    const LocalMapState& m_localMapState;
    GraphicLivingsMap m_graphicLivingsMap;
};

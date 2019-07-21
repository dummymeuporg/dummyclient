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
private:
    const LocalMapState& m_localMapState;
};

#pragma once

#include <memory>
#include <map>
#include <set>
#include <string>

class LocalMapState;

namespace Dummy {
namespace Protocol {
namespace MapUpdate {
class CharacterOff;
class CharacterPosition;
} // namespace MapUpdate
} // namespace Protocol
} // namespace Dummy

namespace Graphics {
class Living;
} // namespace Graphics


using GraphicLivingsMap =
    std::map<std::string, std::unique_ptr<Graphics::Living>>;

class LocalFloorState {
public:
    LocalFloorState(const ::LocalMapState&);
    const GraphicLivingsMap& graphicLivings() {
        return m_graphicLivingsMap;
    }

    void tick();

    bool containsLiving(const std::string& name) const {
        return m_graphicLivingsMap.find(name) != std::end(m_graphicLivingsMap);
    }

    void addLiving(const std::string&, std::unique_ptr<Graphics::Living>);
    void syncLivings();
    void removeLiving(const std::string&);
    void onCharacterPosition(
        const Dummy::Protocol::MapUpdate::CharacterPosition&
    );

    const GraphicLivingsMap& graphicLivings() const {
        return m_graphicLivingsMap;
    }

private:
    const LocalMapState& m_localMapState;
    GraphicLivingsMap m_graphicLivingsMap;
    std::set<std::string> m_idleLivings;

};

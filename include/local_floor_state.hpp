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


using GraphicFoesMap =
    std::map<std::string, std::shared_ptr<Graphics::Living>>;

class LocalFloorState {
public:
    LocalFloorState(const ::LocalMapState&);
    const GraphicFoesMap& graphicFoes() {
        return m_graphicFoesMap;
    }

    void tick();

    bool containsLiving(const std::string& name) const {
        return m_graphicFoesMap.find(name) != std::end(m_graphicFoesMap);
    }

    void addLiving(const std::string&, std::shared_ptr<Graphics::Living>);
    void syncLivings();
    void removeLiving(const std::string&);
    void onCharacterPosition(
        const Dummy::Protocol::MapUpdate::CharacterPosition&
    );

    const GraphicFoesMap& graphicLivings() const {
        return m_graphicFoesMap;
    }

private:
    const LocalMapState& m_localMapState;
    GraphicFoesMap m_graphicFoesMap;
    std::set<std::string> m_idleLivings;

};

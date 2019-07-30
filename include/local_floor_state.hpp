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
class Foe;
} // namespace Graphics


using GraphicFoesMap =
    std::map<std::string, std::shared_ptr<Graphics::Foe>>;

class LocalFloorState {
public:
    LocalFloorState(const ::LocalMapState&);

    void tick();

    bool containsLiving(const std::string& name) const {
        return m_graphicFoesMap.find(name) != std::end(m_graphicFoesMap);
    }

    void addFoe(const std::string&, std::shared_ptr<Graphics::Foe>);
    void removeFoe(const std::string&);
    void onCharacterPosition(
        const Dummy::Protocol::MapUpdate::CharacterPosition&
    );

    const GraphicFoesMap& graphicFoes() const {
        return m_graphicFoesMap;
    }

    void say(const std::string&, const std::string&);

private:
    const LocalMapState& m_localMapState;
    GraphicFoesMap m_graphicFoesMap;
};

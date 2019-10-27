#pragma once

#include <memory>
#include <map>
#include <set>
#include <string>

class LocalMapState;

namespace Dummy {
namespace Protocol {
namespace MapUpdate {
class LivingOff;
class CharacterPosition;
} // namespace MapUpdate
} // namespace Protocol
} // namespace Dummy

namespace Graphics {
class Foe;
} // namespace Graphics


using GraphicFoesMap =
    std::map<std::uint32_t, std::shared_ptr<Graphics::Foe>>;

class LocalFloorState {
public:
    LocalFloorState(const ::LocalMapState&);

    void tick();

    bool containsLiving(std::uint32_t id) const {
        return m_graphicFoesMap.find(id) != std::end(m_graphicFoesMap);
    }

    void addFoe(std::uint32_t, std::shared_ptr<Graphics::Foe>);
    void removeFoe(std::uint32_t);
    void onCharacterPosition(
        const Dummy::Protocol::MapUpdate::CharacterPosition&
    );

    const GraphicFoesMap& graphicFoes() const {
        return m_graphicFoesMap;
    }

    void say(std::uint32_t, const std::string&);

private:
    const LocalMapState& m_localMapState;
    GraphicFoesMap m_graphicFoesMap;
};

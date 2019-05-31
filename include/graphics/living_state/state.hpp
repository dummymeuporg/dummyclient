#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

class Camera;

namespace Graphics {
class Living;
namespace LivingState {

class State : public std::enable_shared_from_this<State> {
public:
    State(Graphics::Living&);
    virtual void draw(sf::RenderWindow&, const Camera&) = 0;
    virtual void moveTowards(std::uint16_t, std::uint16_t) = 0;
protected:
    Graphics::Living& m_living;
};

} // namespace LivingState
} // namespace Graphics

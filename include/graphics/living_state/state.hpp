#pragma once

#include <SFML/Graphics.hpp>

namespace Graphics {
class Living;
namespace LivingState {

class State {
public:
    State(Graphics::Living&);
    virtual void draw(sf::RenderWindow&) = 0;
protected:
    Graphics::Living& m_living;
};

} // namespace LivingState
} // namespace Graphics

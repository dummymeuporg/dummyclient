#pragma once

#include <SFML/Graphics.hpp>

#include "graphics/living_state/state.hpp"

namespace Graphics {
class Living;
namespace LivingState {

class WalkingState : public State {
public:
    WalkingState(Graphics::Living&);
    virtual void draw(sf::RenderWindow&) override;
private:
    std::size_t m_currentFrame;
    sf::Clock m_clock;
};

} // namespace LivingState
} // namespace Graphics

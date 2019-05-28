#pragma once

#include <SFML/Graphics.hpp>

#include "graphics/living_state/state.hpp"

namespace Graphics {
class Living;
namespace LivingState {

class StandingState : public State {
public:
    StandingState(Graphics::Living&);
    virtual void draw(sf::RenderWindow&) override;
};

} // namespace LivingState
} // namespace Graphics

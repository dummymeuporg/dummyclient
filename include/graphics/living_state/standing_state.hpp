#pragma once

#include <SFML/Graphics.hpp>

#include "graphics/living_state/state.hpp"

namespace Graphics {
class Living;
namespace LivingState {

class StandingState : public State {
public:
    StandingState(Graphics::Living&);
    virtual void draw(sf::RenderWindow&, const ::Camera&) override;
    virtual void moveTowards(std::uint16_t x, std::uint16_t y) override;
};

} // namespace LivingState
} // namespace Graphics

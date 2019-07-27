#pragma once

#include <SFML/Graphics.hpp>

#include "graphics/living_state/state.hpp"

namespace Graphics {
class Living;
namespace LivingState {

class StandingState : public State {
public:
    StandingState(Graphics::Living&);
    void draw(sf::RenderWindow&) override;
    void moveTowards(std::uint16_t x, std::uint16_t y) override;
    void walk() override;
    void stand() override;
};

} // namespace LivingState
} // namespace Graphics

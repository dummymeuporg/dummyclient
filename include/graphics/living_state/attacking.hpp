#pragma once

#include <SFML/Graphics.hpp>

#include "graphics/living_state/state.hpp"

namespace Graphics {
class Living;
namespace LivingState {

class Attacking : public State {
public:
    Attacking(Graphics::Living&, int);
    void draw(sf::RenderWindow&) override;
    void moveTowards(std::uint16_t x, std::uint16_t y) override;
    void walk() override;
    void stand() override;
private:
    std::size_t m_currentFrame;
    sf::Clock m_clock;
    int m_refreshFrame;
};

} // namespace LivingState
} // namespace Graphics

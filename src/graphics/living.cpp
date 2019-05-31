#include "camera.hpp"
#include "graphics/living.hpp"
#include "graphics/living_state/standing_state.hpp"

namespace Graphics {

Living::Living(const std::string& chipset,
               const std::string& name,
               std::size_t w,
               std::size_t h,
               std::size_t x,
               std::size_t y,
               Direction direction)
    : Entity(chipset, w, h, x, y),
      m_name(name),
      m_direction(direction),
      m_state(std::make_unique<LivingState::StandingState>(*this))
{}

Living::Living(const Living& living)
    : Entity(living.m_chipsetName, living.m_w, living.m_h, living.m_x,
             living.m_y),
             m_name(living.m_name),
             m_direction(living.m_direction),
             m_state(std::make_unique<LivingState::StandingState>(*this))
{
}


Living& Living::setPosition(std::uint16_t x, std::uint16_t y) {
    m_x = x;
    m_y = y;
    return *this;
}

Living& Living::setDirection(Direction direction) {
    m_direction = direction;
    return *this;
}

Living& Living::changeState(std::shared_ptr<LivingState::State> state) {
    m_state = state;
    return *this;
}

void Living::draw(sf::RenderWindow& window, const ::Camera& camera) {
    m_state->draw(window, camera);
}

void Living::moveTowards(std::uint16_t x, std::uint16_t y) {
    m_state->moveTowards(x, y);
}

} // namespace Graphics

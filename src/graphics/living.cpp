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
               std::size_t scaleFactor,
               Direction direction)
    : Entity(chipset, w, h, x, y, scaleFactor),
      m_name(name),
      m_direction(direction),
      m_state(std::make_unique<LivingState::StandingState>(*this))
{
    _setDisplayName();
}

Living::Living(const Living& living)
    : Entity(living.m_chipsetName, living.m_w, living.m_h, living.m_x,
             living.m_y, living.m_scaleFactor),
             m_name(living.m_name),
             m_direction(living.m_direction),
             m_state(std::make_unique<LivingState::StandingState>(*this))
{
    _setDisplayName();
}

void Living::_setDisplayName() {
    m_displayName.setString(m_name);
    m_displayName.setColor(sf::Color::White);
    m_displayName.setCharacterSize(30);
    m_displayName.setFont(font("arial.ttf"));
    m_displayName.setStyle(sf::Text::Bold);
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
    const sf::Vector2u& windowSize(window.getSize());
    m_state->draw(window, camera);

    sf::FloatRect textRect = m_displayName.getLocalBounds();
    m_displayName.setOrigin(
        textRect.left + textRect.width / 2.0f,
        textRect.top
    );
    m_displayName.setPosition(

        static_cast<int>(windowSize.x / 2) + pixelX() - camera.centerX() +
        w() * 2,
        static_cast<int>(windowSize.y / 2) + pixelY() - camera.centerY() +
        h() * 4
    );
    window.draw(m_displayName);
}

void Living::moveTowards(std::uint16_t x, std::uint16_t y) {
    m_state->moveTowards(x, y);
}

} // namespace Graphics

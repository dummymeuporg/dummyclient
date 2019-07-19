#include "camera.hpp"
#include "map_view.hpp"
#include "graphics/living.hpp"
#include "graphics/living_state/standing_state.hpp"

namespace Graphics {

static const float SQRT_2 = 1.414213562373;

Living::Living(const MapView& mapView,
               const std::string& chipset,
               const std::string& name,
               std::size_t w,
               std::size_t h,
               std::size_t x,
               std::size_t y,
               std::size_t scaleFactor,
               Direction direction,
               std::uint8_t velocity)
    : Entity(mapView, chipset, w, h, x, y, scaleFactor),
      m_name(name),
      m_direction(direction),
      m_state(std::make_unique<LivingState::StandingState>(*this)),
      m_velocity(velocity),
      m_xMovement(0),
      m_yMovement(0)
{
    _setDisplayName();
    m_movingClock.restart();
}

Living::Living(const Living& living)
    : Entity(living.m_mapView,
             living.m_chipsetName,
             living.m_w,
             living.m_h,
             living.m_x,
             living.m_y,
             living.m_scaleFactor),
             m_name(living.m_name),
             m_direction(living.m_direction),
             m_state(std::make_unique<LivingState::StandingState>(*this)),
             m_velocity(living.m_velocity)
{
    _setDisplayName();
}

void Living::_setDisplayName() {
    m_displayName.setString(m_name);
    m_displayName.setColor(sf::Color::White);
    m_displayName.setCharacterSize(15);
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

void Living::tick() {
    /*
    if (m_movingClock.getElapsedTime().asMilliseconds() >= 16 - m_velocity)
    {
        m_x += (m_xMovement * m_scaleFactor);
        m_y += (m_yMovement * m_scaleFactor);
        m_movingClock.restart();
    }
    */
}

std::pair<std::int16_t, std::int16_t>
Living::computeDistance() {
    // If the character is going in a diagonal way, divide its browsed
    // distance by square root of 2 (Pythagor theorem).
    float divisor = m_xMovement != 0 && m_yMovement != 0 ? SQRT_2 : 1.0;
    int ellapsedMs = m_movingClock.getElapsedTime().asMilliseconds();

    std::int16_t xDistance(static_cast<unsigned>(
        ((ellapsedMs/4.5) * m_xMovement) / divisor
    ));
    std::int16_t yDistance(static_cast<unsigned>(
        ((ellapsedMs/4.5) * m_yMovement) / divisor
    ));
    m_movingClock.restart();
    return std::pair<std::int16_t, std::int16_t>(xDistance, yDistance);
}

void Living::draw(sf::RenderWindow& window, const ::Camera& camera) {
    const sf::Vector2u& windowSize(window.getSize());

    // Update position given the ellapsed time and the velocity.
    updatePosition();

    // Update the movement given the effective position
    m_state->draw(window, camera);

    sf::FloatRect textRect = m_displayName.getLocalBounds();
    m_displayName.setOrigin(
        textRect.left + textRect.width / 2.0f,
        textRect.top
    );
    m_displayName.setPosition(

        static_cast<int>(windowSize.x / 2) + m_x - camera.centerX() +
        w() * 1,
        static_cast<int>(windowSize.y / 2) + m_y - camera.centerY() +
        h() * 2
    );
    window.draw(m_displayName);
}

void Living::moveTowards(std::uint16_t x, std::uint16_t y) {
    m_state->moveTowards(x, y);
}

void Living::setVelocity(std::uint8_t velocity) {
    m_velocity = velocity;
}

void Living::setXMovement(int xMovement) {
    m_xMovement = xMovement;
}

void Living::setYMovement(int yMovement) {
    m_yMovement = yMovement;
}

void Living::walk() {
    m_state->walk();
}

void Living::stand() {
    m_state->stand();
}

void Living::updatePosition() {
    auto delta = computeDistance();
    m_x += delta.first;
    m_y += delta.second;
}

} // namespace Graphics

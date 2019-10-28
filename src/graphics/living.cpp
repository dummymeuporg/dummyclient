#include "map_view.hpp"
#include "graphics/living.hpp"
#include "graphics/living_state/standing_state.hpp"

namespace Graphics {

static const float SQRT_2 = 1.414213562373;

Living::Living(const MapView& mapView,
               const std::string& chipset,
               std::size_t w,
               std::size_t h,
               std::int32_t x,
               std::int32_t y,
               std::uint8_t floor,
               std::size_t scaleFactor,
               Direction direction,
               std::uint8_t velocity)
    : Entity(mapView, chipset, w, h, x, y, scaleFactor),
      m_floor(floor),
      m_direction(direction),
      m_state(std::make_unique<LivingState::StandingState>(*this)),
      m_velocity(velocity),
      m_xMovement(0),
      m_yMovement(0),
      m_isSpeaking(false)
{
    initSpeechStuff();
    m_movingClock.restart();
    m_messageToSayClock.restart();
}

Living::Living(const Living& living)
    : Entity(living.m_mapView,
             living.m_chipsetName,
             living.m_w,
             living.m_h,
             living.m_x,
             living.m_y,
             living.m_scaleFactor),
             m_floor(living.m_floor),
             m_direction(living.m_direction),
             m_state(std::make_unique<LivingState::StandingState>(*this)),
             m_velocity(living.m_velocity)
{
    initSpeechStuff();
}

void Living::initSpeechStuff() {

    m_speech.setColor(sf::Color::Black);
    m_speech.setCharacterSize(20);
    m_speech.setFont(font("arial.ttf"));

    m_messageRect.setFillColor(sf::Color(255, 255, 255, 200));
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
}

std::pair<std::int16_t, std::int16_t>
Living::computeDistance() {
    // If the character is going in a diagonal way, divide its browsed
    // distance by square root of 2 (Pythagorean theorem).
    float divisor = m_xMovement != 0 && m_yMovement != 0 ? SQRT_2 : 1.0;
    int ellapsedMs = m_movingClock.getElapsedTime().asMilliseconds();
    auto velocity = static_cast<float>(m_velocity) / 100.0;
    std::int16_t xDistance(static_cast<unsigned>(
        ((ellapsedMs/8.0) * m_xMovement * velocity) / divisor
    ));
    std::int16_t yDistance(static_cast<unsigned>(
        ((ellapsedMs/8.0) * m_yMovement * velocity) / divisor
    ));
    m_movingClock.restart();
    return std::pair<std::int16_t, std::int16_t>(xDistance, yDistance);
}

void Living::draw(sf::RenderWindow& window) {
    // Update position given the ellapsed time and the velocity.
    updatePosition();

    // Update the movement given the effective position
    m_state->draw(window);
}

void Living::drawHUD(sf::RenderWindow& window, const sf::View& view) {
    drawMessage(window, view);
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

void Living::drawMessage(sf::RenderWindow& window, const sf::View& view) {
    if (m_isSpeaking) {
        if (m_messageToSayClock.getElapsedTime().asSeconds() >= 7) {
            m_isSpeaking = false;
            return;
        }

        m_speech.setString(m_messageToSay);
        const auto& origin(m_sprite.getOrigin());
        const auto screenCoords = window.mapCoordsToPixel(
            m_sprite.getPosition(),
            view
        );
        sf::FloatRect textRect = m_speech.getLocalBounds();
        m_speech.setOrigin(
            textRect.left + ((textRect.width+10)/2.0) - origin.x,
            textRect.top - origin.y
        );

        m_speech.setPosition(
            screenCoords.x + m_w/2.0,
            screenCoords.y - m_h*2 - textRect.height
        );
        m_messageRect.setPosition(
            m_speech.getPosition().x - 5,
            m_speech.getPosition().y - 5
        );
        m_messageRect.setOrigin(
            m_speech.getOrigin().x,
            m_speech.getOrigin().y
        );
        m_messageRect.setSize(sf::Vector2f(textRect.width + 10,
                                           textRect.height + 10));
        window.draw(m_messageRect);
        window.draw(m_speech);
    }
}

void Living::say(const std::string& message) {
    m_isSpeaking = true;
    m_messageToSay = message;
    m_messageToSayClock.restart();
}

} // namespace Graphics

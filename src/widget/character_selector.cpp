#include <filesystem>
#include <boost/range/irange.hpp>
#include "widget/character_selector.hpp"

namespace fs = std::filesystem;

namespace Widget {

CharacterSelector::CharacterSelector(Visual& parent)
    : Widget(parent),
      m_selectedCharacter(-1),
      m_backgroundColor(sf::Color(100, 100, 100))
{
}

void CharacterSelector::setPos(std::uint16_t xPos,
                               std::uint16_t yPos)
{
    Widget::setPos(xPos, yPos);
    std::uint16_t xRef(x()), yRef(y());
    for(const auto& i: boost::irange(5))
    {
        sf::RectangleShape& bg(m_backgrounds[i]);

        bg.setPosition(sf::Vector2f(xRef, yRef));
        bg.setSize(sf::Vector2f(24 * 3, 32 * 3));
        bg.setFillColor(m_backgroundColor);

        if (i < m_characters.size()) {
            const auto character = m_characters[i];
            auto& sprite(m_sprites[i]);
            /*
            fs::path chipsetPath(character->skin());
            sprite.setTexture(texture(chipsetPath.string()));
            sprite.setScale(3, 3);
            sprite.setTextureRect(sf::IntRect(24, 32 * 2, 24, 32));
            */
            sprite.setPosition(sf::Vector2f(xRef, yRef));
        }
        xRef += 24*3 + 5;
    }
}

void CharacterSelector::draw(sf::RenderWindow& window)
{
    if (m_characters.size() == 0) {
        return;
    }

    std::uint16_t xRef(x()), yRef(y());

    for(const auto& i: boost::irange(5))
    {
        sf::Color fillColor(m_backgroundColor);
        int delta = 0;
        if (m_selectedCharacter == i) {
            delta = 50;
        } else if (m_hoveredCharacter == i) {
            delta = 25;
        }

        fillColor.r += delta;
        fillColor.g += delta;
        fillColor.b += delta;
            
        sf::RectangleShape& bg(m_backgrounds[i]);
        bg.setFillColor(fillColor);
        window.draw(bg);

        if (i < m_characters.size()) {
            const auto character = m_characters[i];
            auto& sprite(m_sprites[i]);
            window.draw(sprite);
        }
    }
}

bool CharacterSelector::_onMouseButtonPressed(const sf::Event& event)
{
    bool forwardEvent = true;
    if (m_hoveredCharacter >= 0 && event.mouseButton.button == sf::Mouse::Left)
    {
        m_selectedCharacter = m_hoveredCharacter;
        forwardEvent = false;
        pushEvent(CustomEvent(this, CustomEvent::CharacterSelected, nullptr));
        m_hoveredCharacter = -1;
    }
    return forwardEvent;
}

bool CharacterSelector::_onMouseMoved(const sf::Event& event) {
    bool forwardEvent = true;
    m_hoveredCharacter = -1;
    for(const auto& i: boost::irange(m_characters.size())) {
        const sf::Vector2f& origin(m_backgrounds[i].getPosition());
        const sf::FloatRect& bounds(m_backgrounds[i].getLocalBounds());
        if (event.mouseMove.x >= origin.x &&
            event.mouseMove.y >= origin.y &&
            event.mouseMove.x <= (origin.x + bounds.width) &&
            event.mouseMove.y <= (origin.y + bounds.height))
        {
            m_hoveredCharacter = i;
            forwardEvent = false;
            break;
        }
    }
    return forwardEvent;
}

bool CharacterSelector::handleEvent(const sf::Event& event)
{
    bool forwardEvent = true;
    switch(event.type) {
    case sf::Event::MouseMoved:
        forwardEvent = _onMouseMoved(event);
        break;
    case sf::Event::MouseButtonPressed:
        forwardEvent = _onMouseButtonPressed(event);
    default:
        break;
    }
    return forwardEvent;
}

CharacterSelector&
CharacterSelector::setCharacters(const CharactersList& charactersList)
{
    m_characters = charactersList;
    std::uint16_t xRef(x()), yRef(y());
    for (const auto& i: boost::irange(5)) {
        if (i < m_characters.size()) {
            const auto character = m_characters[i];
            auto& sprite(m_sprites[i]);
            fs::path chipsetPath(character->skin());
            sprite.setTexture(texture(chipsetPath.string()));
            sprite.setScale(3, 3);
            sprite.setTextureRect(sf::IntRect(24, 32 * 2, 24, 32));
            sprite.setPosition(sf::Vector2f(xRef, yRef));
            xRef += 24*3 + 5;
        }
    }


    return *this;
}


std::shared_ptr<Dummy::Core::Character>
CharacterSelector::selectedCharacter() const {
    if (m_selectedCharacter >= 0 && m_selectedCharacter < m_characters.size())
    {
        return m_characters[m_selectedCharacter];
    }
    else
    {
        return nullptr;
    }
}

sf::IntRect CharacterSelector::boundingRect() const {
    if (m_backgrounds.size() > 0) {
        auto lastBackground(m_backgrounds[m_backgrounds.size()-1]);
        return sf::IntRect(
            m_x,
            m_y,
            lastBackground.getPosition().x + lastBackground.getSize().x,
            lastBackground.getPosition().y + lastBackground.getSize().y
        );
    } else {
        return sf::IntRect(m_x, m_y, 0, 0);
    }
}

} // namespace Widget

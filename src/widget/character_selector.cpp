#include <filesystem>
#include <boost/range/irange.hpp>
#include "widget/character_selector.hpp"

namespace fs = std::filesystem;

namespace Widget {

CharacterSelector::CharacterSelector(std::shared_ptr<Widget> parent)
    : m_selectedCharacter(-1)
{

}

void CharacterSelector::paint(sf::RenderWindow& window)
{
    if (m_characters.size() == 0) {
        return;
    }

    std::uint16_t xRef(x()), yRef(y());

    for(const auto& i: boost::irange(5))
    {
        sf::RectangleShape& bg(m_backgrounds[i]);

        bg.setPosition(sf::Vector2f(xRef, yRef));
        bg.setSize(sf::Vector2f(24 * 3, 32 * 3));
        bg.setFillColor(sf::Color(100, 100, 100));
        window.draw(bg);

        if (i < m_characters.size()) {
            const auto character = m_characters[i];
            auto& sprite(m_sprites[i]);
            fs::path chipsetPath(character->skin());
            sprite.setTexture(texture(chipsetPath.string()));
            sprite.setScale(3, 3);
            sprite.setTextureRect(sf::IntRect(24, 32 * 2, 24, 32));
            sprite.setPosition(sf::Vector2f(xRef, yRef));
            window.draw(sprite);
        }
        xRef += 24*3 + 5;
    }
}

bool CharacterSelector::handleEvent(const sf::Event& event)
{
    return true;
}

CharacterSelector&
CharacterSelector::setCharacters(const CharactersList& charactersList)
{
    m_characters = charactersList;
    return *this;
}

} // namespace Widget

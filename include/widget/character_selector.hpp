#pragma once

#include "core/character.hpp"
#include "widget/abstract/widget.hpp"

namespace Widget {

class CharacterSelector : public Abstract::Widget {
public:
    using CharactersList =
        std::vector<std::shared_ptr<Dummy::Core::Character>>;
    CharacterSelector(std::shared_ptr<Widget> = nullptr);
    virtual void paint(sf::RenderWindow&) override;
    virtual bool handleEvent(const sf::Event& event) override;
    CharacterSelector& setPos(std::uint16_t, std::uint16_t);
    CharacterSelector& setCharacters(const CharactersList&);
    const CharactersList& characters() const {
        return m_characters;
    }
    std::shared_ptr<const Dummy::Core::Character> selectedCharacter() const;
private:
    bool _onMouseMoved(const sf::Event&);
    bool _onMouseButtonPressed(const sf::Event&);
    bool _onMouseButtonReleased(const sf::Event&);
    int m_selectedCharacter;
    int m_hoveredCharacter;
    CharactersList m_characters;
    sf::Color m_backgroundColor;
    std::array<sf::RectangleShape, 5> m_backgrounds;
    std::array<sf::Sprite, 5> m_sprites;
};

} // namespace Widget

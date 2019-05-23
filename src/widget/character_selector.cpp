#include "widget/character_selector.hpp"

namespace Widget {

CharacterSelector::CharacterSelector(std::shared_ptr<Widget> parent)
    : m_selectedCharacter(-1)
{

}

void CharacterSelector::paint(sf::RenderWindow& window)
{

}

bool CharacterSelector::handleEvent(const sf::Event& event)
{
    return true;
}

} // namespace Widget

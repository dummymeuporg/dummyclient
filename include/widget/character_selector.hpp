#pragma once

#include "widget/abstract/widget.hpp"

namespace Widget {

class CharacterSelector : public Abstract::Widget {
public:
    CharacterSelector(std::shared_ptr<Widget> = nullptr);
    virtual void paint(sf::RenderWindow&) override;
    virtual bool handleEvent(const sf::Event& event) override;
private:
    int m_selectedCharacter;
};

} // namespace Widget

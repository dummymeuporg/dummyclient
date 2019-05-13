#pragma once
#include <sstream>

#include "widget/abstract/widget.hpp"

namespace Widget {

class Textbox : public Abstract::Widget {
public:
    Textbox(std::shared_ptr<Widget>, ::ResourceProvider&, ::CustomEventQueue&);
    virtual void paint(sf::RenderWindow&) override;
    virtual bool handleEvent(const sf::Event& event) override;
    Textbox& setRect(int, int, int, int);
    std::string content() const {
        return m_content.str();
    }
private:
    sf::RectangleShape m_shape;
    std::stringstream m_content;
};

} // namespace Widget

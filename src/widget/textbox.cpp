#include "widget/textbox.hpp"

namespace Widget {

Textbox::Textbox(std::shared_ptr<Widget> parent,
                 ::ResourceProvider& resourceProvider,
                 ::CustomEventQueue& eventQueue)
    : Widget(parent, resourceProvider, eventQueue)
{

}

void Textbox::paint(sf::RenderWindow& renderWindow) {

}

bool Textbox::handleEvent(const sf::Event& event) {
    return true;
}

Textbox& Textbox::setRect(int x, int y, int width, int height) {
    m_shape.setPosition(x, y);
    m_shape.setSize(sf::Vector2f(width, height));
    return *this;
}

} // namespace Widget

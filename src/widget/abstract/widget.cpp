#include "visual.hpp"
#include "widget/abstract/widget.hpp"

namespace Widget {

namespace Abstract {

Widget::Widget(Visual& parent) : m_parent(parent)
{
    auto wptr = std::shared_ptr<Visual>( this, [](Visual*){} );
    m_parent.addChild(shared_from_this());
}


void Widget::setPos(std::uint16_t x, std::uint16_t y) {
    m_x = x;
    m_y = y;
}

void Widget::draw(sf::RenderWindow& window) {

    // Save coordinates, shift according to the parent, shift back.
    auto saveX(m_x);
    auto saveY(m_y);

    setPos(m_x + m_parent.x(), m_y + m_parent.y());
    onDraw(window);
    setPos(saveX, saveY);

    // Draw the children.
    for (auto& child: m_children) {
        child->shared_from_this()->draw(window);
    }
}

bool Widget::handleEvent(const sf::Event& event) {
    bool forwardEvent = true;
    for (auto& child: m_children) {
        forwardEvent = child->shared_from_this()->handleEvent(event);
        if (!forwardEvent) {
            break;
        }
    }
    return forwardEvent;
}

} // namespace Abstract

} // namespace Widget

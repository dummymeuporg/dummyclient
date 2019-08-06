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
    m_x = m_parent.x() + x;
    m_y = m_parent.y() + y;
}

void Widget::draw(sf::RenderWindow& window) {
    for (auto& child: m_children) {
        child->shared_from_this()->draw(window);
    }
}


} // namespace Abstract

} // namespace Widget

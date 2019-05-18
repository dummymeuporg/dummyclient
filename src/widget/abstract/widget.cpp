#include "widget/abstract/widget.hpp"

namespace Widget {

namespace Abstract {

Widget::Widget(std::shared_ptr<Widget> parent)
    : m_parent(parent), m_resourceProvider(ResourceProvider::instance()),
      m_eventQueue(CustomEventQueue::instance()), m_x(0), m_y(0)
{

}

Widget& Widget::setPos(std::uint16_t x, std::uint16_t y) {
    m_x = x;
    m_y = y;
    return *this;
}

bool Widget::handleEvent(const sf::Event& event) {
    return true;
}

} // namespace Abstract

} // namespace Widget

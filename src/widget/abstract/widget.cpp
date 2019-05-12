#include "widget/abstract/widget.hpp"

namespace Widget {

namespace Abstract {

Widget::Widget(std::shared_ptr<Widget> parent,
               ::ResourceProvider& resourceProvider)
    : m_parent(parent), m_resourceProvider(resourceProvider), m_x(0), m_y(0)
{

}

Widget& Widget::setPos(std::uint16_t x, std::uint16_t y) {
    m_x = x;
    m_y = y;
    return *this;
}

} // namespace Abstract

} // namespace Widget
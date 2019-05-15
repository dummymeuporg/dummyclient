#include "widget/skin_picker.hpp"

namespace Widget {

SkinPicker::SkinPicker(std::shared_ptr<Widget> parent)
    : Widget(parent)
{
}

SkinPicker& SkinPicker::setOrigin(int x, int y) {
    m_origin.x = x;
    m_origin.y = y;
    return *this;
}

} // namespace Widget

#include "widget/button.hpp"

namespace Widget {

Button::Button(std::shared_ptr<Widget> parent,
               ::ResourceProvider& resourceProvider)
    : Widget(parent, resourceProvider) {}

Button& setCaption(const std::string& caption) {
    m_caption = caption;
    return *this;
}

} // namespace Widget

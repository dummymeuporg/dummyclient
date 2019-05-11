#include "widget/button.hpp"

namespace Widget {

Button::Button(std::shared_ptr<Widget> parent,
               ::ResourceProvider& resourceProvider)
    : Widget(parent, resourceProvider) {}

Button& Button::setCaption(const std::string& caption) {
    m_caption = caption;
    return *this;
}

void Button::paint(sf::RenderWindow& window) {

}

void Button::handleEvent(const sf::Event& event) {

}

} // namespace Widget

#include "widget/label.hpp"

namespace Widget {

Label::Label(std::shared_ptr<Widget> parent,
               ::ResourceProvider& resourceProvider)
    : Widget(parent, resourceProvider) {}

Label& Label::setCaption(const std::string& caption) {
    m_caption = caption;
    return *this;
}

void Label::paint(sf::RenderWindow& window) {

}

void Label::handleEvent(const sf::Event& event) {

}

} // namespace Widget

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

}

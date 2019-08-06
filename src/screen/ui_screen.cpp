#include "client.hpp"
#include "game.hpp"

#include "screen/ui_screen.hpp"

namespace Screen {

UIScreen::UIScreen(::Game& game, ::Client& client)
    : Screen(game, client)
{
}

UIScreen::~UIScreen() {

}

UIScreen& UIScreen::addWidget(std::shared_ptr<Widget::Abstract::Widget> widget)
{
    m_widgets.push_back(widget);
    return *this;
}

void UIScreen::draw(sf::RenderWindow& window) {
    /*
    for (const auto& widget: m_widgets) {
        widget->draw(window);
    }
    */
    for (auto& child: m_children) {
        auto self(child->shared_from_this());
        self->draw(window);
    }
}

} // namespace Screen

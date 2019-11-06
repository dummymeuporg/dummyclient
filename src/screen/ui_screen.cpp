#include "client.hpp"
#include "game.hpp"

#include "screen/ui_screen.hpp"

namespace Screen {

UIScreen::UIScreen(::Game& game, ::Client& client)
    : Screen(game, client),
      m_uiView(sf::FloatRect(0, 0, game.windowWidth(), game.windowHeight()))
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

    // Save the current view.
    auto currentView(window.getView());

    window.setView(m_uiView);
    for (auto& child: m_children) {
        if (!child->isEnabled()) {
            continue;
        }
        auto self(child->shared_from_this());
        self->draw(window);
    }

    // Restore the current view.
    window.setView(currentView);
}

} // namespace Screen

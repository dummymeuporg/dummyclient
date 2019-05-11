#include "client.hpp"
#include "game.hpp"

#include "screen/ui_screen.hpp"

namespace Screen {

UIScreen::UIScreen(::Game& game,
                   ::Client& client,
                   ::WidgetBuilder& widgetBuilder)
    : Screen(game, client), m_widgetBuilder(widgetBuilder)
{
}

UIScreen& UIScreen::addWidget(std::shared_ptr<Widget::Widget> widget)
{
    m_widgets.push_back(widget);
    return *this;
}

void UIScreen::draw() {
    for (const auto& widget: m_widgets) {
        widget->paint(m_game.window());
    }
}

} // namespace Screen
#include "client.hpp"

#include "screen/ui_screen.hpp"

namespace Screen {

UIScreen::UIScreen(::Game& game,
                   ::Client& client,
                   ::WidgetBuilder& widgetBuilder)
    : Screen(game, client), m_widgetBuilder(widgetBuilder)
{
}

}

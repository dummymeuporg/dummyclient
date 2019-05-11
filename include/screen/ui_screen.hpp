#pragma once

#include "widget_builder.hpp"
#include "screen/screen.hpp"

namespace Screen {

class UIScreen : public Screen {
public:
    UIScreen(::Game&, ::Client&, ::WidgetBuilder&);
    virtual void handleEvent(const sf::Event&) = 0;
    virtual void notify() = 0;
    virtual void draw() = 0;
    ::WidgetBuilder& widgetBuilder() {
        return m_widgetBuilder;
    }
private:
    ::WidgetBuilder& m_widgetBuilder;
};

} // namespace Screen

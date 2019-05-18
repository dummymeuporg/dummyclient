#pragma once

#include "widget_builder.hpp"
#include "screen/screen.hpp"

namespace Screen {

class UIScreen : public Screen {
public:
    UIScreen(::Game&, ::Client&, ::WidgetBuilder&);
    virtual void handleEvent(const sf::Event&) override;
    virtual void handleCustomEvent(const ::CustomEvent&) override;
    virtual void notify();
    virtual void draw();
    ::WidgetBuilder& widgetBuilder() {
        return m_widgetBuilder;
    }
protected:
    UIScreen& addWidget(std::shared_ptr<Widget::Abstract::Widget>);
private:
    ::WidgetBuilder& m_widgetBuilder;
    std::vector<std::shared_ptr<Widget::Abstract::Widget>> m_widgets;
};

} // namespace Screen

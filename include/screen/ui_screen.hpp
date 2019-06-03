#pragma once

#include "widget/abstract/widget.hpp"
#include "screen/screen.hpp"

namespace Screen {

class UIScreen : public Screen {
public:
    UIScreen(::Game&, ::Client&);
    virtual ~UIScreen();
    virtual void handleEvent(const sf::Event&) override;
    virtual void handleCustomEvent(const ::CustomEvent&) override;
    virtual void draw() override;
protected:
    UIScreen& addWidget(std::shared_ptr<Widget::Abstract::Widget>);
private:
    std::vector<std::shared_ptr<Widget::Abstract::Widget>> m_widgets;
};

} // namespace Screen

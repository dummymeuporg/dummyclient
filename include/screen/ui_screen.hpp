#pragma once

#include "widget/abstract/widget.hpp"
#include "screen/screen.hpp"

namespace Screen {

class UIScreen : public Screen {
public:
    UIScreen(::Game&, ::Client&);
    virtual ~UIScreen();
    //bool handleEvent(const sf::Event&) override;
    //void handleCustomEvent(const ::CustomEvent&) override;
    void draw(sf::RenderWindow&) override;
protected:
    UIScreen& addWidget(std::shared_ptr<Widget::Abstract::Widget>);
    sf::View m_uiView;
private:
    std::vector<std::shared_ptr<Widget::Abstract::Widget>> m_widgets;
};

} // namespace Screen

#pragma once

#include <memory>

#include "screen/ui_screen.hpp"
#include "widget/label.hpp"

namespace Screen {

class LoadingScreen : public UIScreen {
public:
    LoadingScreen(::Game&, ::Client&);
    virtual void notify() override;
    virtual void handleCustomEvent(const ::CustomEvent&) override;
private:
    std::shared_ptr<Widget::Label> m_label;
};

} // namespace Screen

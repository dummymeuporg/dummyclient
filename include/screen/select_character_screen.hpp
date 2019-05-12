#pragma once

#include <cstdint>

#include "screen/ui_screen.hpp"
#include "widget/button.hpp"
#include "widget/label.hpp"

namespace Screen {

class SelectCharacterScreen : public UIScreen {
public:
    SelectCharacterScreen(::Game&, ::Client&, ::WidgetBuilder&);
    virtual void notify() override;
    virtual void draw() override;
private:
    std::int16_t m_charactersCount;
    std::shared_ptr<Widget::Button> m_createCharacterButton;
    std::shared_ptr<Widget::Label> m_accountLabel;
    std::shared_ptr<Widget::Label> m_charactersCountLabel;
};

} // namespace Screen

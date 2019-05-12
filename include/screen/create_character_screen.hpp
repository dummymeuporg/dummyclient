#pragma once

#include "screen/ui_screen.hpp"
#include "widget/label.hpp"

namespace Screen {

class CreateCharacterScreen : public UIScreen {
public:
    CreateCharacterScreen(::Game&, ::Client&, ::WidgetBuilder&);
private:
    std::shared_ptr<Widget::Label> m_characterNameLabel; 
};

} // namespace Screen

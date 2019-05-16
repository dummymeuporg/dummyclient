#pragma once

#include "screen/ui_screen.hpp"
#include "widget/label.hpp"
#include "widget/skin_picker.hpp"
#include "widget/textbox.hpp"

namespace Screen {

class CreateCharacterScreen : public UIScreen {
public:
    CreateCharacterScreen(::Game&, ::Client&, ::WidgetBuilder&);
private:
    std::shared_ptr<Widget::Label> m_characterNameLabel; 
    std::shared_ptr<Widget::Textbox> m_characterNameTextbox;
    std::shared_ptr<Widget::Label> m_characterSkinLabel; 
    std::shared_ptr<Widget::SkinPicker> m_skinPicker;
};

} // namespace Screen

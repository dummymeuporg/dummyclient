#pragma once

#include "screen/ui_screen.hpp"
#include "widget/button.hpp"
#include "widget/label.hpp"
#include "widget/skin_previewer.hpp"
#include "widget/textbox.hpp"

namespace Screen {

class CreateCharacterScreen : public UIScreen {
public:
    CreateCharacterScreen(::Game&, ::Client&);
    virtual void notify() override;
    virtual void handleCustomEvent(const ::CustomEvent&) override;
private:
    void _handleButtonClicked(const ::CustomEvent&);
    void _onCreateCharacterButton();
    void _back();
    int m_initialCharactersCount;
    std::shared_ptr<Widget::Label> m_characterNameLabel; 
    std::shared_ptr<Widget::Textbox> m_characterNameTextbox;
    std::shared_ptr<Widget::Label> m_characterSkinLabel; 
    std::shared_ptr<Widget::SkinPreviewer> m_skinPreviewer;
    std::shared_ptr<Widget::Button> m_leftSkinButton;
    std::shared_ptr<Widget::Button> m_rightSkinButton;
    std::shared_ptr<Widget::Button> m_createCharacterButton;
    std::shared_ptr<Widget::Button> m_cancelButton;
};

} // namespace Screen

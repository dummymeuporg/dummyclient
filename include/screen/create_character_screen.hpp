#pragma once

#include "screen/ui_screen.hpp"
#include "widget/button.hpp"
#include "widget/label.hpp"
#include "widget/skin_previewer.hpp"
#include "widget/textbox.hpp"


namespace Dummy {
namespace Core {
class Character;
} // namespace Core
} // namespace Dummy

namespace Screen {

class CreateCharacterScreen : public UIScreen {
public:
    CreateCharacterScreen(
        ::Game&,
        ::Client&,
        std::vector<std::shared_ptr<Dummy::Core::Character>>&
    );
    ~CreateCharacterScreen() override;
    virtual void handleCustomEvent(const ::CustomEvent&) override;

    virtual void
    onResponse(const Dummy::Server::Response::Response& response) override;

    virtual void visitResponse(
        const Dummy::Server::Response::CreateCharacter&
    ) override;
private:
    void handleButtonClicked(const ::CustomEvent&);
    void onCreateCharacterButton();
    void back();
    std::vector<std::shared_ptr<Dummy::Core::Character>>& m_characters;
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

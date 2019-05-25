#pragma once

#include <cstdint>

#include "screen/ui_screen.hpp"
#include "widget/button.hpp"
#include "widget/label.hpp"
#include "widget/character_selector.hpp"

namespace Screen {

class SelectCharacterScreen : public UIScreen {
public:
    SelectCharacterScreen(::Game&, ::Client&);
    virtual void notify() override;
    virtual void handleCustomEvent(const ::CustomEvent&) override;
private:
    std::int16_t m_charactersCount;
    std::shared_ptr<Widget::Button> m_createCharacterButton;
    std::shared_ptr<Widget::Button> m_playButton;
    std::shared_ptr<Widget::Label> m_accountLabel;
    std::shared_ptr<Widget::Label> m_charactersCountLabel;
    std::shared_ptr<Widget::SkinPreviewer> m_skinPreviewer;
    std::shared_ptr<Widget::CharacterSelector> m_characterSelector;
};

} // namespace Screen

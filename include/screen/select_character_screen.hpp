#pragma once

#include <cstdint>

#include "model/characters_list_model.hpp"
#include "screen/ui_screen.hpp"
#include "widget/button.hpp"
#include "widget/label.hpp"
#include "widget/character_selector.hpp"
#include "widget/skin_previewer.hpp"

namespace Screen {

class SelectCharacterScreen : public UIScreen {
public:
    SelectCharacterScreen(::Game&, ::Client&);
    virtual ~SelectCharacterScreen();
    virtual void handleCustomEvent(const ::CustomEvent&) override;
    virtual void loaded();
    virtual void accept(std::shared_ptr<Model::Model> model) override {
        model->visit(
            std::reinterpret_pointer_cast<SelectCharacterScreen>(
                shared_from_this()
            )
        );
    }
    void
    setCharacters(
        const Model::CharactersListModel::CharactersList& charactersList
    );
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

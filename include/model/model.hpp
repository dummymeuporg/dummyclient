#pragma once

#include <memory>
#include <set>

#include "game_element.hpp"
#include "model/errors.hpp"

namespace Screen {
    class Screen;
    class CreateCharacterScreen;
    class GameScreen;
    class LoadingScreen;
    class SelectCharacterScreen;
}

namespace Model {

class Model : public std::enable_shared_from_this<Model>,
              public ::GameElement {
public:
    Model();
    virtual ~Model();
    void update();
    void addScreen(std::shared_ptr<Screen::Screen>);
    void removeScreen(std::shared_ptr<Screen::Screen>);

    virtual void visit(std::shared_ptr<Screen::CreateCharacterScreen>) {
        throw ScreenNotHandled();
    }
    virtual void visit(std::shared_ptr<Screen::GameScreen>) {
        throw ScreenNotHandled();
    }
    virtual void visit(std::shared_ptr<Screen::LoadingScreen>) {
        throw ScreenNotHandled();
    }
    virtual void visit(std::shared_ptr<Screen::SelectCharacterScreen>) {
        ScreenNotHandled(); 
    }


private:
    std::set<std::shared_ptr<Screen::Screen>> m_screens;
};

} // namespace Model

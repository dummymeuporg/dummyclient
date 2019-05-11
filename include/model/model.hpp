#pragma once

#include <memory>
#include <set>

namespace Screen {
    class Screen;
}

namespace Model {

class Model {
public:
    Model();
    void update();
    void addScreen(std::shared_ptr<Screen::Screen>);
    void removeScreen(std::shared_ptr<Screen::Screen>);
private:
    std::set<std::shared_ptr<Screen::Screen>> m_screens;
};

} // namespace Model

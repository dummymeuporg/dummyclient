#include "screen/screen.hpp"
#include "model/model.hpp"

namespace Model {

Model::Model()
{}

void Model::update() {
    for(const auto& screen: m_screens) {
        screen->notify();
    }
}

void Model::addScreen(std::shared_ptr<Screen::Screen> screen) {
    if(m_screens.find(screen) == std::end(m_screens)) {
        m_screens.insert(screen);
    }
}

void Model::removeScreen(std::shared_ptr<Screen::Screen> screen) {
    if (m_screens.find(screen) != std::end(m_screens)) {
        m_screens.erase(screen);
    }
}

} // namespace Model

#include <iostream>

#include "screen/screen.hpp"
#include "model/model.hpp"

namespace Model {

Model::Model()
{}

Model::~Model() {
    std::cerr << "Model destructor." << std::endl;
}

void Model::update() {
    std::cerr << "Will notify screens. " << m_screens.size() << std::endl;
    for(const auto& screen: m_screens) {
        std::cerr << "Notify screen." << std::endl;
        screen->notify();
    }
}

void Model::addScreen(std::shared_ptr<Screen::Screen> screen) {
    if(m_screens.find(screen) == std::end(m_screens)) {
        std::cerr << "insert screen." << std::endl;
        m_screens.insert(screen);
    }
}

void Model::removeScreen(std::shared_ptr<Screen::Screen> screen) {
    auto self(shared_from_this());
    if (m_screens.find(screen) != std::end(m_screens)) {
        std::cerr << "Erase screen." << std::endl;
        m_screens.erase(screen);
    }
}

} // namespace Model

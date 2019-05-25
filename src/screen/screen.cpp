#include "client.hpp"

#include "model/model.hpp"
#include "screen/screen.hpp"

namespace Screen {
Screen::Screen(::Game& game, ::Client& client)
    : m_game(game), m_client(client), m_model(nullptr)
{
}

Screen::~Screen() {
    std::cerr << "screen destructor." << std::endl;
}

void Screen::detachFromModel() {
    auto self(shared_from_this());
    if (m_model != nullptr)
    {
        m_model->removeScreen(self);
        m_model = nullptr;
    }
}

void Screen::setModel(std::shared_ptr<Model::Model> model) {
    auto self(shared_from_this());
    if (m_model != nullptr)
    {
        m_model->removeScreen(self);
    }
    m_model = model;
    m_model->addScreen(self);
}

} // namespace Screen

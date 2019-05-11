#include "client.hpp"

#include "model/model.hpp"
#include "screen/screen.hpp"

namespace Screen {
Screen::Screen(sf::RenderWindow& window, ::Client& client)
    : m_window(window), m_client(client)
{
}

Screen::~Screen() {
    m_model->removeScreen(shared_from_this());
}

void Screen::setModel(std::shared_ptr<Model::Model> model) {
    if (m_model != nullptr)
    {
        m_model->removeScreen(shared_from_this());
    }
    m_model = model;
    m_model->addScreen(shared_from_this());
}

} // namespace Screen

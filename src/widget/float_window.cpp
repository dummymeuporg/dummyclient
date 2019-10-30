#include "widget/float_window.hpp"

namespace Widget {

FloatWindow::FloatWindow(Visual& parent) : Widget(parent) {
}

void FloatWindow::draw(sf::RenderWindow& window) {
    // draw whole shape
    m_window.setPosition(50, 50);
    m_window.setSize(sf::Vector2f(400, 300));
    m_window.setFillColor(sf::Color(183, 109, 44, 200));
    window.draw(m_window);
    // ...

    m_statusBar.setPosition(50, 50);
    m_statusBar.setSize(sf::Vector2f(400, 24));
    m_statusBar.setFillColor(sf::Color(133, 59, 14));
    window.draw(m_statusBar);

    m_closeButton.setPosition(450 - 24, 50);
    m_closeButton.setSize(sf::Vector2f(24, 24));
    m_closeButton.setFillColor(sf::Color(127, 127, 127));
    window.draw(m_closeButton);

    // draw top status bar.
}

bool FloatWindow::handleEvent(const sf::Event& event) {
    return true;
}

sf::IntRect FloatWindow::boundingRect() {
    return sf::IntRect(m_x, m_x, m_width, m_height);
}

} // namespace Widget

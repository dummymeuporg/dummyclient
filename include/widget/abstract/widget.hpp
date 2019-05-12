#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "resource_provider.hpp"

namespace Widget {

namespace Abstract {

class Widget : public std::enable_shared_from_this<Widget> {
public:
    Widget(std::shared_ptr<Widget>, ::ResourceProvider&);
    virtual void paint(sf::RenderWindow&) = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;
    Widget& setPos(std::uint16_t, std::uint16_t);

    std::uint16_t x() const {
        return m_x;
    }

    std::uint16_t y() const {
        return m_y;
    }

    std::shared_ptr<Widget> parent() const {
        return m_parent;
    }

protected:
    sf::Font& font(const std::string& fontName) {
        return m_resourceProvider.font(fontName);
    }
    
private:
    std::shared_ptr<Widget> m_parent;
    ::ResourceProvider& m_resourceProvider;
    std::uint16_t m_x, m_y;

};

} // namespace Abstract

} // namespace Widget
#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "custom_event_queue.hpp"
#include "resource_provider.hpp"

namespace Widget {

namespace Abstract {

class Widget : public std::enable_shared_from_this<Widget> {
public:
    Widget(std::shared_ptr<Widget> = nullptr);
    virtual void paint(sf::RenderWindow&) = 0;
    virtual bool handleEvent(const sf::Event& event);
    virtual bool handleCustomEvent(const ::CustomEvent& event);
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

    sf::Texture& texture(const std::string& textureName) {
        return m_resourceProvider.texture(textureName);
    }

    void pushEvent(const CustomEvent& event) {
        m_eventQueue.pushEvent(event);
    }
    
private:
    std::shared_ptr<Widget> m_parent;
    ::ResourceProvider& m_resourceProvider;
    ::CustomEventQueue& m_eventQueue;
    std::uint16_t m_x, m_y;

};

} // namespace Abstract

} // namespace Widget

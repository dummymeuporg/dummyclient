#pragma once

#include <memory>
#include <set>

#include <SFML/Graphics.hpp>

#include "game_element.hpp"

class Game;

class Visual : public std::enable_shared_from_this<Visual>,
               public ::GameElement
{
public:
    Visual();
    virtual ~Visual();
    virtual void draw(sf::RenderWindow&) = 0;
    virtual bool handleEvent(const sf::Event&);
    virtual bool handleCustomEvent(const ::CustomEvent&);

    virtual void setPos(std::uint16_t, std::uint16_t);
    virtual void setSize(std::uint16_t, std::uint16_t);

    virtual sf::IntRect boundingRect() const = 0;

    std::uint16_t x() const {
        return m_x;
    }

    std::uint16_t y() const {
        return m_y;
    }

    std::uint16_t width() const {
        return m_width;
    }

    std::uint16_t height() const {
        return m_height;
    }

    bool isEnabled() const {
        return m_isEnabled;
    }

    bool isMouseHovering() {
        return m_isMouseHovering;
    }

    void addChild(std::shared_ptr<Visual>);
    void removeChild(std::shared_ptr<Visual>);
    void setEnabled(bool);
    void setMouseHovering(bool);
protected:
    void focusChild(const Visual* child);
    void resetHovering();

    ::ResourceProvider& m_resourceProvider;
    ::CustomEventQueue& m_eventQueue;
    std::uint16_t m_x, m_y;
    std::uint16_t m_width, m_height;
    std::set<std::shared_ptr<Visual>> m_children;

    Visual* m_focusedChild;
    Visual* m_hoveredChild;

    bool m_isEnabled;
    bool m_isMouseHovering;
    bool m_isBeingClicked;
    bool m_isFocused;
private:
    bool onMouseMoved(const sf::Event&);
    bool onMouseButtonPressed(const sf::Event&);
    bool onMouseButtonReleased(const sf::Event&);
    bool handleSelfCustomEvent(const ::CustomEvent&);

};

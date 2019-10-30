#include "visual.hpp"

Visual::Visual()
    : m_resourceProvider(ResourceProvider::instance()),
      m_eventQueue(CustomEventQueue::instance()), m_x(0), m_y(0),
      m_focusedChild(nullptr),
      m_hoveredChild(nullptr),
      m_isEnabled(true),
      m_isMouseHovering(false),
      m_isBeingClicked(false)
{}

void Visual::setPos(std::uint16_t x, std::uint16_t y) {
    m_x = x;
    m_y = y;
}

void Visual::setSize(std::uint16_t width, std::uint16_t height) {
    m_width = width;
    m_height = height;
}

void Visual::addChild(std::shared_ptr<Visual> child) {
    m_children.emplace(child);
}

void Visual::removeChild(std::shared_ptr<Visual> child) {
    m_children.erase(child);
}

bool Visual::onMouseButtonPressed(const sf::Event& event) {
    bool forwardEvent(true);
    if (nullptr != m_hoveredChild && !m_isBeingClicked) {
        m_isBeingClicked = true;
        forwardEvent = m_hoveredChild->onMouseButtonPressed(event);
    }
    return forwardEvent;
}

bool Visual::onMouseButtonReleased(const sf::Event& event) {
    bool forwardEvent(true);
    if (nullptr != m_hoveredChild && m_isBeingClicked) {
        m_isBeingClicked = false;
        pushEvent(CustomEvent(
            this,
            CustomEvent::Type::LeftClick,
            m_hoveredChild)
        );
        forwardEvent = m_hoveredChild->onMouseButtonReleased(event);
    }
    return forwardEvent;
}

bool Visual::onMouseMoved(const sf::Event& event) {
    bool forwardEvent(true);

    // First of all, check about the hovered child, if any.
    if (nullptr != m_hoveredChild) {
        const auto& boundingRect(m_hoveredChild->boundingRect());
        if (!boundingRect.contains(event.mouseMove.x, event.mouseMove.y)) {
            m_hoveredChild->setMouseHovering(false);
            std::cerr << "Pushing mouse left" << std::endl;
            pushEvent(CustomEvent(
                this,
                CustomEvent::Type::MouseLeft,
                m_hoveredChild
            ));
            m_hoveredChild = nullptr;
        }
    }

    // Check if the mouse is in a child region
    for(auto& child: m_children) {
        if (child->isEnabled()) {
            const auto& boundingRect(child->boundingRect());
            // Do not handle invisible widgets.
            if (boundingRect.width == 0 || boundingRect.height == 0) {
                continue;
            }
            if (boundingRect.contains(event.mouseMove.x, event.mouseMove.y)) {
                // If the child has no mouse hovering, toggle the state
                // and send an appropriate message.
                if (!child->isMouseHovering()) {
                    m_hoveredChild = child.get();
                    child->setMouseHovering(true);
                    std::cerr << "Pushing mouse entered" << std::endl;
                    pushEvent(CustomEvent(
                        this,
                        CustomEvent::Type::MouseEntered,
                        m_hoveredChild
                    ));

                }
                return child->onMouseMoved(event);
            }
        }
    }
    return forwardEvent;
}

bool Visual::handleEvent(const sf::Event& event) {
    bool forwardEvent(true);
    switch(event.type) {
    case sf::Event::MouseMoved:
         forwardEvent = onMouseMoved(event);
        break;
    case sf::Event::MouseButtonPressed:
        forwardEvent = onMouseButtonPressed(event);
        break;
    case sf::Event::MouseButtonReleased:
        forwardEvent = onMouseButtonReleased(event);
        break;
    default:
        break;
    }

    if (forwardEvent) {
        for(auto& child: m_children) {
            if (!child->isEnabled()) {
                continue;
            }
            if(!child->handleEvent(event)) {
                return false;
            }
        }
    }
    return forwardEvent;
}


void Visual::handleCustomEvent(const ::CustomEvent& event) {
    for (auto& child: m_children) {
        if (!child->isEnabled()) {
            continue;
        }
        if (event.target() == child.get() || event.target() == nullptr) {
            child->handleCustomEvent(event);
        }
    }
}

void Visual::setEnabled(bool enabled) {
    m_isEnabled = enabled;
}

void Visual::setMouseHovering(bool hovering) {
    m_isMouseHovering = hovering;
}

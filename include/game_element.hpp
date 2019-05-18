#pragma once

#include "custom_event_queue.hpp"
#include "resource_provider.hpp"

class GameElement {
public:
    GameElement() :
        m_customEventQueue(::CustomEventQueue::instance()),
        m_resourceProvider(::ResourceProvider::instance())
    {}

    virtual void handleCustomEvent(const ::CustomEvent&)
    {}

protected:
    sf::Font& font(const std::string& fontName) {
        return m_resourceProvider.font(fontName);
    }

    sf::Texture& texture(const std::string& textureName) {
        return m_resourceProvider.texture(textureName);
    }

    void pushEvent(const ::CustomEvent& event) {
        m_customEventQueue.pushEvent(event);
    }

private:
    ::CustomEventQueue& m_customEventQueue;
    ::ResourceProvider& m_resourceProvider;
};

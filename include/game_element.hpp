#pragma once

#include "graphics/map.hpp"
#include "custom_event_queue.hpp"
#include "resource_provider.hpp"

class GameElement {
public:
    GameElement() :
        m_customEventQueue(::CustomEventQueue::instance()),
        m_resourceProvider(::ResourceProvider::instance())
    {}

    virtual bool handleCustomEvent(const ::CustomEvent&)
    { return true; }

protected:
    sf::Font& font(const std::string& fontName) {
        return m_resourceProvider.font(fontName);
    }

    sf::SoundBuffer& sound(const std::string& soundName) {
        return m_resourceProvider.sound(soundName);
    }

    sf::Texture& texture(const std::string& textureName) {
        return m_resourceProvider.texture(textureName);
    }

    std::unique_ptr<Graphics::Map> loadGraphicMap(
        const std::string& mapName
    ) {
        return m_resourceProvider.loadGraphicMap(mapName);
    }

    void pushEvent(const ::CustomEvent& event) {
        m_customEventQueue.pushEvent(event);
    }

    void pushEvent(CustomEvent&& event) {
        m_customEventQueue.pushEvent(std::move(event));
    }

private:
    ::CustomEventQueue& m_customEventQueue;
    ::ResourceProvider& m_resourceProvider;
};

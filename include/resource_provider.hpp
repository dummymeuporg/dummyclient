#pragma once

#include "graphics/map.hpp"
#include <dummy/local/project.hpp>
#include <dummy/utils/singleton.hpp>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class ResourceProviderError : public std::exception {

};

class FontLoadingError : public ResourceProviderError {
public:
    virtual const char* what() const noexcept override {
        return "could not load font";
    }
};

class TextureLoadingError : public ResourceProviderError {
public:
    virtual const char* what() const noexcept override {
        return "could not load texture";
    }
};

class SoundLoadingError : public ResourceProviderError {
public:
    virtual const char* what() const noexcept override {
        return "could not load sound";
    }
};

class ResourceProvider : public Singleton<ResourceProvider> {
public:
    ResourceProvider();
    sf::Font& font(const std::string&);
    sf::Texture& texture(const std::string&);
    sf::SoundBuffer& sound(const std::string&);

    std::unique_ptr<Graphics::Map>
        loadGraphicMap(const std::string&);

private:
    std::map<std::string, sf::Font> m_fonts;
    std::map<std::string, sf::Texture> m_textures;
    std::map<std::string, sf::SoundBuffer> m_sounds;
    Dummy::Local::Project m_localProject;

};

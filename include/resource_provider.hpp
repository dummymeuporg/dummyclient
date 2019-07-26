#pragma once

#include "graphics/map.hpp"
#include <dummy/local/project.hpp>
#include <dummy/utils/singleton.hpp>
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


class ResourceProvider : public Singleton<ResourceProvider> {
public:
    ResourceProvider();
    sf::Font& font(const std::string&);
    sf::Texture& texture(const std::string&);

    std::unique_ptr<Graphics::Map>
        loadGraphicMap(const std::string&);

private:
    std::map<std::string, sf::Font> m_fonts;
    std::map<std::string, sf::Texture> m_textures;
    Dummy::Local::Project m_localProject;

};

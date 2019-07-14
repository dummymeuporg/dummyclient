#include <filesystem>
#include <iostream>
#include <string>
#include "local/project.hpp"
#include "graphics/map.hpp"
#include "resource_provider.hpp"

namespace fs = std::filesystem;

ResourceProvider::ResourceProvider()
    : m_localProject(std::string(".")) {}

sf::Font& ResourceProvider::font(const std::string& fontName) {
    if (m_fonts.find(fontName) == std::end(m_fonts)) {
        sf::Font font;
        if(!font.loadFromFile(fontName))
        {
            throw ::FontLoadingError();
        }
        m_fonts[fontName] = std::move(font);
    }
    return m_fonts[fontName];
}

sf::Texture& ResourceProvider::texture(const std::string& textureName) {
    std::cerr << "Ask for texture " << textureName << std::endl;
    fs::path fullPath(std::move(fs::path("chipsets")) / textureName);
    const std::string& textureKey(fullPath.string());
    if (m_textures.find(textureKey) == std::end(m_textures))
    {
        sf::Texture texture;
        std::cerr << "File is " << textureKey;
        if (!texture.loadFromFile(textureKey)) {
            throw ::TextureLoadingError();
        }
        m_textures[textureKey] = std::move(texture);

    }
    return m_textures[textureKey];
}

std::unique_ptr<Graphics::Map>
ResourceProvider::loadGraphicMap(const std::string& mapName) {
    std::unique_ptr<Graphics::Map> map =
        std::make_unique<Graphics::Map>(m_localProject, mapName);
    map->load();
    return map;
}

#include <filesystem>
#include <iostream>
#include "resource_provider.hpp"

namespace fs = std::filesystem;

ResourceProvider::ResourceProvider() {}

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

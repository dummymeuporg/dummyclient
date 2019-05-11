#include "resource_provider.hpp"

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

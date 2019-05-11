#pragma once

#include <SFML/Graphics.hpp>

class ResourceProviderError : public std::exception {

};

class FontLoadingError : public ResourceProviderError {
    virtual const char* what() const noexcept override {
        return "could not load font";
    }
};


class ResourceProvider {
public:
    ResourceProvider();
    sf::Font& font(const std::string&);

private:
    std::map<std::string, sf::Font> m_fonts;

};

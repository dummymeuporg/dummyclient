#pragma once

#include <exception>
#include <filesystem>

#include <boost/property_tree/ptree.hpp>

#include <SFML/Graphics.hpp>

namespace fs = std::filesystem;

class ConfigError : public std::exception {

};

class InvalidPort : public ConfigError {
public:
    virtual const char* what() const noexcept override {
        return "the port is invalid.";
    }
};

class Config {
public:
    Config(const fs::path&);

    std::uint16_t port() const {
        return m_port;
    }

    const std::string& host() const {
        return m_host;
    }

    sf::Keyboard::Key upKey() const {
        return m_upKey;
    }

    sf::Keyboard::Key leftKey() const {
        return m_leftKey;
    }

    sf::Keyboard::Key downKey() const {
        return m_downKey;
    }

    sf::Keyboard::Key rightKey() const {
        return m_rightKey;
    }

private:
    void readConfigFile();
    void readKeyStrokes(const boost::property_tree::ptree&);

    fs::path m_configPath;
    std::uint16_t m_port;
    std::string m_host;

    sf::Keyboard::Key m_upKey;
    sf::Keyboard::Key m_leftKey;
    sf::Keyboard::Key m_downKey;
    sf::Keyboard::Key m_rightKey;

};


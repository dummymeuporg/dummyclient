#pragma once

#include <exception>
#include <filesystem>

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
private:
    void _readConfigFile();

    fs::path m_configPath;
    std::uint16_t m_port;
    std::string m_host;
};


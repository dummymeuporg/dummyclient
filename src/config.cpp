#include <iostream>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "config.hpp"

Config::Config(const fs::path& path) :
    m_configPath(path)
{
    readConfigFile();
}

void Config::readConfigFile() {
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini(m_configPath.string(), pt);

    readKeyStrokes(pt);

    /*
    m_host = pt.get<std::string>("server.host");
    std::istringstream iss (std::move(pt.get<std::string>("server.port")));
    iss >> m_port;
    if (iss.bad()) {
        throw InvalidPort();
    }
    */
}


void Config::readKeyStrokes(const boost::property_tree::ptree& pt) {
    int data;
    std::istringstream iss(pt.get<std::string>("Keystrokes.up"));
    iss >> data;
    m_upKey = static_cast<sf::Keyboard::Key>(data);

    iss.str(pt.get<std::string>("Keystrokes.down"));
    iss.clear();

    iss >> data;
    m_downKey = static_cast<sf::Keyboard::Key>(data);

    iss.str(pt.get<std::string>("Keystrokes.right"));
    iss.clear();

    iss >> data;
    m_rightKey = static_cast<sf::Keyboard::Key>(data);

    iss.str(pt.get<std::string>("Keystrokes.left"));
    iss.clear();

    iss >> data;
    m_leftKey = static_cast<sf::Keyboard::Key>(data);

}

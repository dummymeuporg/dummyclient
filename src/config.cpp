#include <iostream>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "config.hpp"

Config::Config(const fs::path& path) :
    m_configPath(path)
{
    _readConfigFile();
}

void Config::_readConfigFile() {
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini(m_configPath.string(), pt);
    m_host = pt.get<std::string>("server.host");
    std::istringstream iss (std::move(pt.get<std::string>("server.port")));
    iss >> m_port;
    if (iss.bad()) {
        throw InvalidPort();
    }
}

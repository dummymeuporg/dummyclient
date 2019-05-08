#pragma once

#include <cstdint>
#include <string>

#include <boost/uuid/uuid.hpp>

class Credentials {
public:
    Credentials(const std::string&, const std::string&); 
    
    const std::string& account() const {
        return m_account;
    }

    const std::uint8_t* sessionID() const {
        return m_sessionID.data;
    }

private:
    std::string m_account;
    boost::uuids::uuid m_sessionID;
};

#pragma once

#include <cstdint>
#include <string>

class Credentials {
public:
    Credentials(const std::string&, const std::string&); 
    
    const std::string& account() const {
        return m_account;
    }

    const std::string& sessionID() const {
        return m_sessionID;
    }

private:
    std::string m_account;
    std::string m_sessionID;
};

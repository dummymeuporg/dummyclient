#include "credentials.hpp"

Credentials::Credentials(const std::string& accountName,
                         const std::string& sessionID)
    : m_account(accountName), m_sessionID(sessionID)
{}

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "credentials.hpp"

using namespace boost::uuids;

Credentials::Credentials(const std::string& accountName,
                         const std::string& sessionID)
    : m_account(accountName)
{
    string_generator gen;
    m_sessionID = gen(sessionID);
}

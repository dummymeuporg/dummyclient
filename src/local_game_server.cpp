#include "server/account.hpp"
#include "local_game_server.hpp"


LocalGameServer::LocalGameServer(const fs::path& projectPath,
                                 const fs::path& serverPath)
    : Dummy::Server::AbstractGameServer(projectPath, serverPath)
{
}

void LocalGameServer::_instantiateTestAccount(
    const std::string& accountName, const std::string& sessionID
)
{
    std::string testAccountName(accountName);
    fs::path accountPath(
        m_serverPath / "accounts" / testAccountName
    );
    if (!fs::exists(accountPath)) {
        std::cerr << "Test account directory does not exist. Create it."
            << std::endl;
        fs::create_directory(accountPath);
        fs::create_directory(accountPath / "characters");
    }

    Dummy::Server::Account account(
        testAccountName,
        sessionID
    );

    std::cerr << "Connect to the server using " << testAccountName
        << " and " << account.sessionID() << std::endl;
    m_pendingAccounts[account.sessionID()] =
        std::make_shared<Dummy::Server::Account>(account);
}

void LocalGameServer::run() {
    _instantiateTestAccount(
        "TEST.0000", "00000000-0000-0000-0000-000000000000"
    );
}

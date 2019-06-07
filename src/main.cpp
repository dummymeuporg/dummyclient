#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "server/game_session.hpp"

#include "config.hpp"
#include "connector/local_connector.hpp"
#include "connector/network_connector.hpp"
#include "local_game_server.hpp"
#include "game.hpp"

namespace fs = std::filesystem;

int run_standalone(const char* projectPath, const char* serverPath,
                   const char* account, const char* sessionID)
{
    ::LocalGameServer server(projectPath, serverPath);
    server.run(); // create the account
    std::shared_ptr<Dummy::Server::GameSession> session =
        server.buildGameSession();
    session->start();
    Connector::LocalConnector connector(*session);
    ::Config config("dummyclient.ini");
    ::Game game(account, sessionID, connector, config);
    return game.run();
}

int run_remote(const char* host, unsigned short port, const char* account,
               const char* sessionID)
{
    Connector::NetworkConnector connector(host, port);
    connector.connect();
    ::Config config("dummyclient.ini");
    ::Game game(account, sessionID, connector, config);
    return game.run();
}

int main(int argc, char* argv[])
{
    if (argc < 6)
    {
        std::cerr << "Usage: "
            << argv[0] << " [standalone <project_path> <server_path>|"
            << "remote <host> <port>] <account> <session_id> "
            << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string connectorType(argv[1]);
    if (connectorType == "standalone") {
        return run_standalone(argv[2], argv[3], argv[4], argv[5]);
    } else if (connectorType == "remote") {
        return run_remote(argv[2], atoi(argv[3]), argv[4], argv[5]);
    } else {
        return EXIT_FAILURE;
    }
}


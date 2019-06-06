#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "server/game_session.hpp"

#include "config.hpp"
#include "connector/local_connector.hpp"
#include "local_game_server.hpp"
#include "game.hpp"

namespace fs = std::filesystem;

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
    ::Config config("dummyclient.ini");

    // XXX: dirty.
    std::string connectorType(argv[1]);
    if (connectorType == "standalone") {
        ::LocalGameServer server(argv[2], argv[3]);
        server.run(); // create the account
        std::shared_ptr<Dummy::Server::GameSession> session =
            server.buildGameSession();
        session->start();
        Connector::LocalConnector connector(*session);
        ::Game game(argv[4], argv[5], connector, config);
        return game.run();
    } else {
        // XXX: instantiate network connector
        ::exit(EXIT_FAILURE);
    }

}


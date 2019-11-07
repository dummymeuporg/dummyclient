#include <cstdlib>
#include <iostream>
#include <filesystem>

#include <boost/asio.hpp>
#include <SFML/Graphics.hpp>

#include <dummy/server/game_session.hpp>
#include <dummy/server/game_session_communicator.hpp>

#include "config.hpp"
#include "connector/local_connector.hpp"
#include "connector/network_connector.hpp"
#include "local_game_server.hpp"
#include "game.hpp"

namespace fs = std::filesystem;

int run_standalone(const char* projectPath,
                   const char* serverPath/*,
                   const char* account,
                   const char* sessionID*/)
{

    boost::asio::io_context iocontext;
    auto communicator(
        std::make_shared<Dummy::Server::GameSessionCommunicator>(iocontext)
    );

    ::LocalGameServer server(iocontext, projectPath, serverPath);
    server.run(); // create the account

    auto session = server.buildGameSession(communicator);
    session->start();

    auto connector(std::make_shared<Connector::LocalConnector>(communicator));
    connector->start();
    ::Config config("dummyclient.ini");
    //::Game game(account, sessionID, connector);
    ::Game game(
        "TEST.0000",
        "00000000-0000-0000-0000-000000000000",
        *connector,
        config
    );

    // XXX: this line prevents the iocontext from completing.
    // Think about a less messy solution on the mean term.
    auto work = std::make_shared<boost::asio::io_context::work>(iocontext);
    std::thread serverThread{[&iocontext](){
        iocontext.run();
    }};

    int ret = game.run();
    work.reset();

    iocontext.stop();
    serverThread.join();

    session->close();
    return ret;
}

int run_remote(const char* host, unsigned short port, const char* account,
               const char* sessionID)
{
    Connector::NetworkConnector connector(host, port);
    connector.start();
    ::Config config("dummyclient.ini");
    ::Game game(account, sessionID, connector, config);
    return game.run();
}

[[ noreturn ]] void usage(char* argv[])  {
    std::cerr << "Usage: "
        << argv[0] << " [standalone <project_path> <server_path>|"
        << "remote <host> <port>] <account> <session_id> "
        << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        usage(argv);
    }

    std::string connectorType(argv[1]);
    if (connectorType == "standalone") {
        return run_standalone(argv[2], argv[3]/*, argv[4], argv[5]*/);
    } else if (connectorType == "remote") {
        if (argc < 6) {
            usage(argv);
        }
        return run_remote(argv[2], atoi(argv[3]), argv[4], argv[5]);
    } else {
        return EXIT_FAILURE;
    }
}


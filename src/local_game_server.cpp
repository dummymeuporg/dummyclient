#include "local_game_server.hpp"


LocalGameServer::LocalGameServer(const fs::path& projectPath,
                                 const fs::path& serverPath)
    : Dummy::Server::AbstractGameServer(projectPath, serverPath)
{
}

void LocalGameServer::run() {

}

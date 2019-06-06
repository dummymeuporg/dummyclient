#pragma once
#include <filesystem>

#include "server/abstract_game_server.hpp"

namespace fs = std::filesystem;

class LocalGameServer : public Dummy::Server::AbstractGameServer {
public:
    LocalGameServer(const fs::path&, const fs::path&);
    virtual void run() override;
};

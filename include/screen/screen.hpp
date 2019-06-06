#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "server/response/response_visitor.hpp"
#include "game_element.hpp"

class CustomEvent;
class Client;
class Game;

namespace Dummy {
namespace Server {
namespace Response {
class Response;
} // namespace Response
} // namespace Server
} // namespace Dummy

namespace Screen {

class Screen : public std::enable_shared_from_this<Screen>,
               public ::GameElement,
               public Dummy::Server::Response::ResponseVisitor
{
public:
    Screen(::Game&, ::Client&);
    virtual ~Screen();
    virtual void handleEvent(const sf::Event&) = 0;
    virtual void draw() = 0;
    virtual void tick();
    virtual void loaded();
    virtual void returned();
    virtual void
    onResponse(const Dummy::Server::Response::Response& response) = 0;

protected:
    ::Game& m_game;
    ::Client& m_client;
};

} // namespace Screen

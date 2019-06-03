#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "game_element.hpp"

class CustomEvent;
class Client;
class Game;

namespace Model {
    class Model;
}

namespace Screen {

class Screen : public std::enable_shared_from_this<Screen>,
               public ::GameElement
{
public:
    Screen(::Game&, ::Client&);
    virtual ~Screen();
    virtual void handleEvent(const sf::Event&) = 0;
    virtual void draw() = 0;
    virtual void tick();
    virtual void loaded();
    virtual void accept(std::shared_ptr<Model::Model> model) = 0;

protected:
    ::Game& m_game;
    ::Client& m_client;
};

} // namespace Screen

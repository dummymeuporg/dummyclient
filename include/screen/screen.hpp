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
    void setModel(std::shared_ptr<Model::Model>);
    virtual void handleEvent(const sf::Event&) = 0;
    virtual void notify() = 0;
    virtual void draw() = 0;

protected:
    ::Game& m_game;
    ::Client& m_client;
    std::shared_ptr<Model::Model> m_model;
};

} // namespace Screen

#pragma once

#include <memory>

class Client;
class Game;

namespace Model {
    class Model;
}

namespace Screen {

class Screen : public std::enable_shared_from_this<Screen> {
public:
    Screen(::Game&, ::Client&);
    virtual ~Screen();
    void setModel(std::shared_ptr<Model::Model>);
    virtual void notify() = 0;
    virtual void draw() = 0;

protected:
    ::Game& m_game;
    ::Client& m_client;
    std::shared_ptr<Model::Model> m_model;
};

} // namespace Screen

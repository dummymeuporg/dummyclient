#pragma once

#include <memory>
#include "local_map_state.hpp"
#include "level_view.hpp"
#include "map_view.hpp"
#include "graphics/player.hpp"
#include "screen/ui_screen.hpp"

class Client;
class Game;

namespace Widget {
class Chatbox;
class QuitMessage;
} // namespace Widget

namespace Screen {

using GraphicLivingsMap = 
    std::map<std::string, std::unique_ptr<Graphics::Living>>;

class GameScreen : public UIScreen {
public:
	static const int DIRECTION_NONE = 0x00;
	static const int DIRECTION_UP = 0x01;
	static const int DIRECTION_RIGHT = 0x02;
	static const int DIRECTION_DOWN = 0x04;
	static const int DIRECTION_LEFT = 0x08;
	static const int DIRECTION_ALL = 0x0f;

    GameScreen(::Game&,
               ::Client&,
               std::unique_ptr<::MapView>);
    virtual ~GameScreen();
    void loaded() override;
    bool handleEvent(const sf::Event&) override;
    void handleCustomEvent(const ::CustomEvent&) override;
    void draw(sf::RenderWindow&) override;
    void tick() override;

    void
    onResponse(const Dummy::Server::Response::Response& response) override;

    void visitResponse(const Dummy::Server::Response::Message&) override;
    void visitResponse(const Dummy::Server::Response::Ping&) override;
    void visitResponse(const Dummy::Server::Response::SetPosition&) override;

private:
    /* Private methods. */
    void drawLayer(::Sprites&);
    void drawCharacter();
    void onKeyPressed(const sf::Event&);
    void onKeyReleased(const sf::Event&);
    void onTextEntered(const sf::Event&);
    void onArrowPressed();
    void onArrowReleased();
    void moveCharacter(sf::Keyboard::Key);
    void drawLivings(std::uint8_t);
    void syncLivings();
    void drawLevelView(unsigned int, LevelView&);
    void drawBlockingLayer(unsigned int, LevelView&);
    void drawSprites(Sprites&);
    void toggleEscapeMode();
    void buildEscapeMessage();
    void removeEscapeMessage();

    /* Private attributes. */
    std::unique_ptr<::MapView> m_mapView;
    Graphics::Player m_player;
    GraphicLivingsMap m_livings;
    bool m_isArrowPressed;
    sf::Keyboard::Key m_direction;
    sf::Clock m_tickMove;
    sf::Clock m_pingClock;
	unsigned int m_characterDirection;
	bool m_isMoving;
    ::LocalMapState m_mapState;
    sf::View m_gameView, m_hudView;
    bool m_debugMode;

    std::shared_ptr<Widget::Chatbox> m_chatbox;

    // XXX: This screen class start to be messy. The different states
    // managed by a bool should be, well, better handled.
    bool m_isTypingMessage;
    bool m_isEnterKeyPressed;

    // XXX: same as above.
    bool m_isEscapeKeyPressed;
    bool m_isEscapeMode;
    std::shared_ptr<Widget::QuitMessage> m_quitMessage;
};

} // namespace Screen

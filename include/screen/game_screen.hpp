#pragma once

#include <memory>
#include "local_map_state.hpp"
#include "camera.hpp"
#include "level_view.hpp"
#include "map_view.hpp"
#include "graphics/player.hpp"
#include "screen/ui_screen.hpp"

class Client;
class Game;

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
    void handleEvent(const sf::Event&) override;
    void handleCustomEvent(const ::CustomEvent&) override;
    void draw() override;
    void tick() override;

    void
    onResponse(const Dummy::Server::Response::Response& response) override;
    void visitResponse(const Dummy::Server::Response::Ping&) override;
    void visitResponse(const Dummy::Server::Response::SetPosition&) override;

private:
    /* Private methods. */
    void drawLayer(::Sprites&);
    void drawCharacter();
    void onKeyPressed(const sf::Event&);
    void onKeyReleased(const sf::Event&);
    void onArrowPressed();
    void onArrowReleased();
    void moveCharacter(sf::Keyboard::Key);
    void drawLivings(std::uint8_t);
    void syncLivings();
    void drawLevelView(unsigned int, LevelView&);
    void drawSprites(Sprites&);

    /* Private attributes. */
    std::unique_ptr<::MapView> m_mapView;
    Camera m_camera;
    Graphics::Player m_player;
    GraphicLivingsMap m_livings;
    bool m_isArrowPressed;
    sf::Keyboard::Key m_direction;
    sf::Clock m_tickMove;
    sf::Clock m_pingClock;
	unsigned int m_characterDirection;
	bool m_isMoving;
    ::LocalMapState m_mapState;
    sf::View m_view;
};

} // namespace Screen

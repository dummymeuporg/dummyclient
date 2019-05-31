#pragma once

#include <memory>
#include "camera.hpp"
#include "map_view.hpp"
#include "graphics/player.hpp"
#include "screen/ui_screen.hpp"

namespace Screen {

class GameScreen : public UIScreen {
public:
    GameScreen(::Game&, ::Client&, std::unique_ptr<::MapView>);
    virtual void notify() override;
    virtual void loaded() override;
    virtual void handleEvent(const sf::Event&);
    virtual void handleCustomEvent(const ::CustomEvent&);
    virtual void draw() override;
    virtual void tick() override;
private:
    /* Private methods. */
    void _drawLayer(::Sprites&);
    void _drawCharacter();
    void _onKeyPressed(const sf::Event&);
    void _onKeyReleased(const sf::Event&);
    void _onArrowPressed();
    void _onArrowReleased();
    void _moveCharacter(sf::Keyboard::Key);
    void _drawLivings();
    void _syncLivings();

    /* Private attributes. */
    std::unique_ptr<::MapView> m_mapView;
    Camera m_camera;
    Graphics::Player m_player;
    std::map<std::string, std::shared_ptr<Graphics::Living>> m_livings;
    bool m_isArrowPressed;
    sf::Keyboard::Key m_direction;
    sf::Clock m_tickMove;
    sf::Clock m_pingClock;
    sf::Clock m_syncLivingsClock;
};

} // namespace Screen

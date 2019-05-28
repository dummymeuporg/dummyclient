#pragma once

#include <memory>
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
private:
    void _drawLayer(::Sprites&);
    void _drawCharacter();
    void _onKeyPressed(const sf::Event&);
    void _onKeyReleased(const sf::Event&);
    void _onArrowPressed();
    void _onArrowReleased();
    std::unique_ptr<::MapView> m_mapView;
    std::uint16_t m_originX, m_originY;
    Graphics::Player m_player;
    bool m_isArrowPressed;
};

} // namespace Screen

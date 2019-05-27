#pragma once

#include <memory>
#include "map_view.hpp"
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
    void _onKeyPressed(const sf::Event& event);
    std::unique_ptr<::MapView> m_mapView;
    std::uint16_t m_originX, m_originY;
};

} // namespace Screen

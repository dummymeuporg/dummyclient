#pragma once

#include "floor_view.hpp"

#include "screen/game_screen_state/state.hpp"

namespace Screen {
namespace GameScreenState {

class PlayingState : public State {
public:
    void draw(sf::RenderWindow&) override;
    void tick() override;
private:
    void drawFloorView(unsigned int, ::FloorView&);
    void drawFloorViewHUD(unsigned int, FloorView&);
    void drawSprites(Sprites&);
    void drawBlockingLayer(unsigned int, FloorView&);
    void drawCharacter();
    void drawCharacterHUD();
};

} // namespace GameScreenState
} // namespace Screen

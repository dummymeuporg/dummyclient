#pragma once

#include <screen/game_screen.hpp>
#include <screen/game_screen_state/state.hpp>

namespace Screen {

namespace GameScreenState {

State::State(GameScreen& gameScreen) : m_gameScreen(gameScreen) {}

State::~State() {}

} // namespace GameScreenState
} // namespace Screen

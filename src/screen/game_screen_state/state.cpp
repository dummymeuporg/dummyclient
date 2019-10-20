#include <screen/game_screen.hpp>
#include <screen/game_screen_state/state.hpp>

namespace Screen {

namespace GameScreenState {

State::State(GameScreen& gameScreen)
    : m_gameScreen(gameScreen),
      m_mapView(gameScreen.mapView()),
      m_player(gameScreen.player()),
      m_livings(gameScreen.livings()),
      m_mapState(gameScreen.mapState()),
      m_gameView(gameScreen.gameView()),
      m_hudView(gameScreen.hudView()),
      m_client(gameScreen.client()),
      m_game(gameScreen.game())
{}

State::~State() {}

} // namespace GameScreenState
} // namespace Screen

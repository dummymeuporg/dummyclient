#include "model/playing_model.hpp"
#include "screen/game_screen.hpp"

namespace Model {

PlayingModel::PlayingModel() {}

PlayingModel::~PlayingModel() {}

void PlayingModel::addLiving(const std::string& name,
                             std::shared_ptr<Graphics::Living> living)
{
    m_livings[name] = living;
}

void PlayingModel::removeLiving(const std::string& name) {
    m_livings.erase(name);
}


void
PlayingModel::visit(std::shared_ptr<Screen::GameScreen> screen) {
    screen->syncWithModel(
        std::reinterpret_pointer_cast<PlayingModel>(shared_from_this())
    );
}

} // namespace Model

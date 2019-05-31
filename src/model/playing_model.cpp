#include "model/playing_model.hpp"

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

} // namespace Model

#include "model/loading_model.hpp"

namespace Model {

LoadingModel::LoadingModel() {}

LoadingModel::~LoadingModel() {}

void LoadingModel::setStatus(std::uint8_t status) {
    m_status = status;
}


void LoadingModel::visit(std::shared_ptr<Screen::LoadingScreen> screen) {
    if (m_status != 0) {
        pushEvent(
            CustomEvent(
                reinterpret_cast<void*>(shared_from_this().get()),
                CustomEvent::MapViewLoaded,
                reinterpret_cast<void*>(screen.get())
            )
        );
    }
}

} // namespace Model

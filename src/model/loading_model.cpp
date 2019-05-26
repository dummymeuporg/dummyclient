#include "model/loading_model.hpp"

namespace Model {

LoadingModel::LoadingModel() {}

LoadingModel::~LoadingModel() {}

void LoadingModel::setStatus(std::uint8_t status) {
    m_status = status;
}

} // namespace Model

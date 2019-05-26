#pragma once

#include "model/model.hpp"

namespace Model {

class LoadingModel : public Model {
public:
    LoadingModel();
    virtual ~LoadingModel();
    std::uint8_t status() const {
        return m_status;
    }

    void setStatus(std::uint8_t status);
private:
    std::uint8_t m_status;
};

} // namespace Model

#pragma once

#include <cstdint>
#include <utility>

class Camera {
public:
    Camera(std::uint16_t, std::uint16_t);
    Camera(const std::pair<std::uint16_t, std::uint16_t>&);

    std::uint16_t centerX() const {
        return m_center.first;
    }

    std::uint16_t centerY() const {
        return m_center.second;
    }

    const std::pair<std::uint16_t, std::uint16_t>& center() const {
        return m_center;
    }

    void setCenter(std::uint16_t, std::uint16_t);
    void setCenter(const std::pair<std::uint16_t, std::uint16_t>&);


    void moveUp();
    void moveRight();
    void moveDown();
    void moveLeft();
private:
    std::pair<std::uint16_t, std::uint16_t> m_center;

};

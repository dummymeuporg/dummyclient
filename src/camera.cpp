#include "camera.hpp"

Camera::Camera(std::uint16_t x, std::uint16_t y)
    : m_center(x, y)
{}

Camera::Camera(const std::pair<std::uint16_t, std::uint16_t>& center) :
    m_center(center)
{}

void Camera::setCenter(std::uint16_t x, std::uint16_t y) {
    m_center.first = x;
    m_center.second = y;
}


void Camera::setCenter(const std::pair<std::uint16_t, std::uint16_t>& center)
{
    setCenter(center.first, center.second);
}


void Camera::moveUp() {
    if (m_center.second > 0) {
        --m_center.second;
    }
}

void Camera::moveRight() {
    ++m_center.first;
}

void Camera::moveDown() {
    ++m_center.second;
}

void Camera::moveLeft() {
    if (m_center.first > 0) {
        --m_center.first;
    }
}

#pragma once

#include "graphics/living.hpp"

class Client;
class MapView;

namespace Graphics {

class Player : public Living {
public:
    Player(
        const ::MapView&,
        ::Client&,
        const std::string& chipset,
        const std::string& name,
        std::int32_t x,
        std::int32_t y,
        std::uint8_t floor,
        std::uint16_t scaleFactor,
        Direction direction = Direction::DOWN
    );

    void tick() override;
    void draw(sf::RenderWindow&) override;
    void drawHUD(sf::RenderWindow&, const sf::View&) override;
    const std::pair<std::uint16_t, std::uint16_t>& serverPosition() const {
        return m_serverPosition;
    }
protected:
    void updatePosition() override;

    void moveTowardsRight(int);
    void moveTowardsLeft(int);
    void moveTowardsTop(int);
    void moveTowardsBottom(int);

    bool blocksLeft() const;
    bool blocksRight() const;
    bool blocksTop() const;
    bool blocksBottom() const;

    void setDisplayName();

    sf::Text& displayName() {
        return m_displayName;
    }

    std::pair<std::uint16_t, std::uint16_t>
    translateCoordsToServ(std::int32_t, std::int32_t);
    ::Client& m_client;
    sf::Clock m_updatePosClock;
    std::pair<std::uint16_t, std::uint16_t> m_serverPosition;
    std::string m_name;
    sf::Text m_displayName;
};

} // namespace Graphics

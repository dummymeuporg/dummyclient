#pragma once

#include <memory>
#include "graphics/living_state/state.hpp"
#include "graphics/entity.hpp"

namespace Graphics {

class Living : public Entity {
public:
    enum Direction {
        UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3
    };
    Living(const std::string&,
           std::size_t,
           std::size_t,
           std::size_t,
           std::size_t);
    virtual void draw(sf::RenderWindow&) override;
    const Direction& direction() const {
        return m_direction;
    }

    Living& setDirection(Direction);
    Living& changeState(std::unique_ptr<LivingState::State>);
protected:
    Direction m_direction;
    std::unique_ptr<LivingState::State> m_state;
};

} // namespace Graphics

#pragma once

#include <cstdint>

#include "screen/screen.hpp"

namespace Screen {

class SelectCharacterScreen : public Screen {
public:
    SelectCharacterScreen(::Game&, ::Client&);
    virtual void notify() override;
    virtual void draw() override;
private:
    std::uint16_t m_charactersCount;
};

} // namespace Screen

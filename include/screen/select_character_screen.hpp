#pragma once

#include <cstdint>

#include "screen/ui_screen.hpp"

namespace Screen {

class SelectCharacterScreen : public UIScreen {
public:
    SelectCharacterScreen(::Game&, ::Client&, ::WidgetBuilder&);
    virtual void handleEvent(const sf::Event&) override;
    virtual void notify() override;
    virtual void draw() override;
private:
    std::int16_t m_charactersCount;
};

} // namespace Screen

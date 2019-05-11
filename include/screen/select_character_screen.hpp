#pragma once

#include "screen/screen.hpp"

namespace Screen {

class SelectCharacterScreen : public Screen {
public:
    SelectCharacterScreen(::Game&, ::Client&);
    virtual void notify() override;
    virtual void draw() override;
private:
    sf::Font m_arialFont;
    //std::unique_ptr<
};

} // namespace Screen

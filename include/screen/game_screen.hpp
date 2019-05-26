#pragma once

#include <memory>
#include "map_view.hpp"
#include "screen/ui_screen.hpp"

namespace Screen {

class GameScreen : public UIScreen {
public:
    GameScreen(::Game&, ::Client&, std::unique_ptr<::MapView>);
    virtual void notify() override;
    virtual void loaded() override;
    virtual void handleCustomEvent(const ::CustomEvent&);
    virtual void draw() override;
private:
    std::unique_ptr<::MapView> m_mapView;
};

} // namespace Screen

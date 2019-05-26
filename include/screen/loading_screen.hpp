#pragma once

#include <memory>

#include "map_view.hpp"
#include "screen/ui_screen.hpp"
#include "widget/label.hpp"

namespace Screen {

class LoadingScreen : public UIScreen {
public:
    LoadingScreen(::Game&, ::Client&, const std::string&);
    virtual void notify() override;
    virtual void loaded() override;
    virtual void handleCustomEvent(const ::CustomEvent&) override;
private:
    std::string m_mapNameToLoad;
    std::shared_ptr<Widget::Label> m_label;
    std::unique_ptr<Dummy::Core::GraphicMap> m_graphicMap;
    std::unique_ptr<::MapView> m_mapView;
};

} // namespace Screen

#pragma once

#include <memory>

#include "map_view.hpp"
#include "screen/ui_screen.hpp"
#include "widget/label.hpp"

namespace Graphics {
class Map;
} // namespace Graphics

namespace Screen {

class LoadingScreen : public UIScreen {
public:
    LoadingScreen(::Game&, ::Client&, const std::string&, const std::string&);
    virtual ~LoadingScreen();
    void loaded() override;
    void handleCustomEvent(const ::CustomEvent&) override;

    void onResponse(const Dummy::Server::Response::Response&) override;

    void visitResponse(const Dummy::Server::Response::TeleportMap&) override;
private:
    std::string m_mapNameToLoad;
    std::string m_instance;
    std::shared_ptr<Widget::Label> m_label;
    std::unique_ptr<Graphics::Map> m_map;
    std::unique_ptr<::MapView> m_mapView;
};

} // namespace Screen

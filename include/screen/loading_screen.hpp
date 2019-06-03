#pragma once

#include <memory>

#include "map_view.hpp"
#include "screen/ui_screen.hpp"
#include "widget/label.hpp"

namespace Screen {

class LoadingScreen : public UIScreen {
public:
    LoadingScreen(::Game&, ::Client&, const std::string&);
    virtual ~LoadingScreen();
    virtual void loaded() override;
    virtual void handleCustomEvent(const ::CustomEvent&) override;
    virtual void accept(std::shared_ptr<Model::Model> model) override {
        model->visit(
            std::reinterpret_pointer_cast<LoadingScreen>(shared_from_this())
        );
    }
private:
    std::string m_mapNameToLoad;
    std::shared_ptr<Widget::Label> m_label;
    std::unique_ptr<Dummy::Core::GraphicMap> m_graphicMap;
    std::unique_ptr<::MapView> m_mapView;
};

} // namespace Screen

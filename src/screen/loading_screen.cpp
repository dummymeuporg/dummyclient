#include <iostream>

#include "screen/loading_screen.hpp"

namespace Screen {

LoadingScreen::LoadingScreen(
    ::Game& game,
    ::Client& client,
    const std::string& mapNameToLoad
)
    : UIScreen(game, client),
      m_mapNameToLoad(mapNameToLoad),
      m_label(std::make_shared<Widget::Label>()),
      m_graphicMap(nullptr),
      m_mapView(nullptr)
{
    m_label
        ->setCaption("Loading...")
        .setFontSize(50)
        .setColor(sf::Color::White)
        .setStyle(sf::Text::Bold)
        .setFont("arial.ttf");

    sf::Text& caption(m_label->caption());
    sf::FloatRect textRect = caption.getLocalBounds();
    caption.setOrigin(textRect.left + textRect.width/2.0f,
                      textRect.top + textRect.height/2.0f);
    caption.setPosition(1024/2, 768/2);

    addWidget(m_label);
}

void LoadingScreen::loaded() {
    pushEvent(
        CustomEvent(
            reinterpret_cast<void*>(shared_from_this().get()),
            CustomEvent::LoadMapFromFile,
            reinterpret_cast<void*>(shared_from_this().get())
        )
    );
}

void LoadingScreen::notify() {

}

void LoadingScreen::handleCustomEvent(const ::CustomEvent& event)
{
    switch(event.type()) {
    case CustomEvent::Type::LoadMapFromFile:
        std::cerr << "Load map " << m_mapNameToLoad
            << " from file" << std::endl;
        m_graphicMap = loadGraphicMap(m_mapNameToLoad);
        std::cerr << "map " << m_mapNameToLoad << " loaded." << std::endl;
        pushEvent(
            CustomEvent(
                reinterpret_cast<void*>(shared_from_this().get()),
                CustomEvent::MapFileLoaded,
                reinterpret_cast<void*>(shared_from_this().get())
            )
        );
        break;
    case CustomEvent::Type::MapFileLoaded:
        std::cerr << "Load map view" << std::endl;
        m_mapView = std::make_shared<::MapView>(std::move(m_graphicMap));
        std::cerr << "Loaded map view. Switch to gamescreen." << std::endl;
        break; 
    default:
        break;
    }
}

} // namespace Screen

#pragma once

#include "floor_view.hpp"

#include "screen/game_screen_state/state.hpp"

#include "widget/chatbox.hpp"
#include "widget/quit_message.hpp"

namespace Screen {
namespace GameScreenState {

class Playing : public State {
public:
    static const int DIRECTION_NONE = 0x00;
    static const int DIRECTION_UP = 0x01;
    static const int DIRECTION_RIGHT = 0x02;
    static const int DIRECTION_DOWN = 0x04;
    static const int DIRECTION_LEFT = 0x08;
    static const int DIRECTION_ALL = 0x0f;

    Playing(GameScreen&);
    void draw(sf::RenderWindow&) override;
    void tick() override;
    void loaded() override;
    void
    visitResponse(const Dummy::Server::Response::Message&) override;

    void
    visitResponse(const Dummy::Server::Response::Ping&) override;

    void
    visitResponse(const Dummy::Server::Response::SetPosition&) override;

    void
    visitResponse(const Dummy::Server::Response::ChangeCharacter&) override;

    void
    visitResponse(const Dummy::Server::Response::TeleportMap&) override;

    void onTeleport(
        const std::string&,
        std::uint16_t,
        std::uint16_t,
        std::uint8_t
    ) override;

    void onMessage(const std::string& message) override;

    bool handleEvent(const sf::Event&) override;
    void handleCustomEvent(const ::CustomEvent&) override;

private: /* Methods. */
    void buildEscapeMessage();
    void drawBlockingLayer(unsigned int, FloorView&);
    void drawCharacter();
    void drawCharacterHUD();
    void drawFloorView(unsigned int, ::FloorView&);
    void drawFloorViewHUD(unsigned int, FloorView&);
    void drawLayer(::Sprites&);
    void drawLivings(std::uint8_t);
    void drawSprites(Sprites&);
    void moveCharacter(sf::Keyboard::Key);
    void onKeyPressed(const sf::Event&);
    void onKeyReleased(const sf::Event&);
    void onTextEntered(const sf::Event&);
    void onArrowPressed();
    void onArrowReleased();
    void removeEscapeMessage();
    void syncLivings();
    void toggleEscapeMode();


private: /* Attributes. */
    unsigned int m_characterDirection;
    sf::Keyboard::Key m_direction;

    bool m_isArrowPressed;
    bool m_isMoving;
    bool m_debugMode;
    bool m_isTypingMessage;
    bool m_isEnterKeyPressed;
    bool m_isEscapeKeyPressed;
    bool m_isEscapeMode;
    bool m_isTeleporting;

    sf::Clock m_tickMove;
    sf::Clock m_pingClock;

    std::shared_ptr<Widget::Chatbox> m_chatbox;
    std::shared_ptr<Widget::QuitMessage> m_quitMessage;
};

} // namespace GameScreenState
} // namespace Screen

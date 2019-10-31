#pragma once

#include "widget/modal_message.hpp"


namespace Widget {

class QuitMessage : public ModalMessage {
public:
    QuitMessage(Visual&);
    bool handleCustomEvent(const ::CustomEvent&) override;
    bool onLeftClick(const ::CustomEvent& event);
private:
    std::shared_ptr<Button> m_quitButton;
    std::shared_ptr<Button> m_changeCharacterButton;
    std::shared_ptr<Button> m_cancelButton;
};

} // namespace Widget

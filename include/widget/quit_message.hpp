#pragma once

#include "widget/modal_message.hpp"


namespace Widget {

class QuitMessage : public ModalMessage {
public:
    QuitMessage(Visual&);
private:
    std::shared_ptr<Button> m_quitButton;
    std::shared_ptr<Button> m_changeCharacterButton;
    std::shared_ptr<Button> m_cancelButton;
};

} // namespace Widget

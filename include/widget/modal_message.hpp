#pragma once

#include <memory>
#include <vector>

#include "widget/abstract/widget.hpp"
#include "widget/button.hpp"
#include "widget/label.hpp"

namespace Widget {

class ModalMessage : public Abstract::Widget {
public:
    ModalMessage(std::shared_ptr<Widget> = nullptr);
    void paint(sf::RenderWindow&) override;
    bool handleEvent(const sf::Event &event) override;
    void addButton(std::shared_ptr<Button>);
    void setMessage(const std::string&);
protected:
    sf::RectangleShape m_backgroundRectangle;
    std::shared_ptr<Label> m_message;
    std::vector<std::shared_ptr<Button>> m_buttons;
};

} // namespace Widget

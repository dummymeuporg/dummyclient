#pragma once

#include <memory>
#include <vector>

#include "widget/abstract/widget.hpp"
#include "widget/button.hpp"
#include "widget/label.hpp"

namespace Widget {

class ModalMessage : public Abstract::Widget {
public:
    ModalMessage(Visual&, const std::string&);
    void draw(sf::RenderWindow&) override;
    void addButton(std::shared_ptr<Button>);
    void setMessage(const std::string&);
    void setSize(std::uint16_t, std::uint16_t) override;
    void setPos(std::uint16_t, std::uint16_t) override;
protected:
    sf::RectangleShape m_backgroundRectangle;
    std::shared_ptr<Label> m_message;
    std::vector<std::shared_ptr<Button>> m_buttons;
};

} // namespace Widget

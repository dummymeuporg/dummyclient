#pragma once

#include "widget/widget.hpp"

namespace Widget {

class Label : public Widget {
public:
    Label(std::shared_ptr<Widget>, ::ResourceProvider&);
    virtual void paint(sf::RenderWindow&) override;
    virtual void handleEvent(const sf::Event& event) override;
    const std::string& caption() const {
        return m_caption;
    }
    Label& setCaption(const std::string&);
private:
    std::string m_caption;
};

};

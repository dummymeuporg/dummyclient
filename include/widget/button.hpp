#pragma once

#include "widget/widget.hpp"

namespace Widget {

class Button : public Widget {
public:
    Button(std::shared_ptr<Widget>, ::ResourceProvider&);
    virtual void paint() override;
    virtual void handleEvent(const sf::Event& event) override;
    const std::string& caption() const {
        return m_caption;
    }
    Button& setCaption(const std::string&);
private:
    std::string m_caption;
};

};

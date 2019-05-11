#pragma once

#include "widget/widget.hpp"

class ResourceProvider;

class WidgetBuilder {
public:
    WidgetBuilder(::ResourceProvider&);

    template<typename T>
    std::shared_ptr<T>
    build(std::shared_ptr<Widget::Widget> parent = nullptr) {
        return std::make_shared<T>(parent, m_resourceProvider);
    }

    // XXX: should not be accessed.
    ::ResourceProvider& resourceProvider() {
        return m_resourceProvider;
    }

private:
    ::ResourceProvider& m_resourceProvider;
};

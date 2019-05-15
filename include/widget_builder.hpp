#pragma once

#include "custom_event_queue.hpp"
#include "widget/abstract/widget.hpp"

class ResourceProvider;

class WidgetBuilder {
public:
    WidgetBuilder(::ResourceProvider&, ::CustomEventQueue&);

    template<typename T>
    std::shared_ptr<T>
    build(std::shared_ptr<Widget::Abstract::Widget> parent = nullptr) {
        return std::make_shared<T>(parent);
    }

    // XXX: should not be accessed.
    ::ResourceProvider& resourceProvider() {
        return m_resourceProvider;
    }

private:
    ::ResourceProvider& m_resourceProvider;
    ::CustomEventQueue& m_eventQueue;
};

#include "resource_provider.hpp"
#include "widget_builder.hpp"

WidgetBuilder::WidgetBuilder(::ResourceProvider& resourceProvider,
                             ::CustomEventQueue& customEventQueue)
    : m_resourceProvider(resourceProvider), m_eventQueue(customEventQueue)
{

}

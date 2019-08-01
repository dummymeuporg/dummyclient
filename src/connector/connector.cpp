#include <dummy/server/response/response.hpp>

#include "connector/connector.hpp"

namespace Connector {

void Connector::handleResponse(ResponsePtr response) {
    m_responses.emplace(std::move(response));
}

ResponsePtr Connector::getResponse() {
    if (m_responses.size() > 0) {
        auto response(std::move(m_responses.front()));
        m_responses.pop();
        return response;
    }
    return nullptr; // no response
}

void Connector::commandHandlerClosed() {
    //m_gameSessionCommunicator = nullptr;
}


} // namespace Connector

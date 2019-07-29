#include <dummy/server/response/response.hpp>

#include "connector/connector.hpp"

namespace Connector {

void
Connector::handleResponse(ResponsePtr response) {
    m_responses.emplace(std::move(response));
}

ResponsePtr Connector::getResponse() {
    if (m_responses.size() > 0) {
        std::unique_ptr<const Dummy::Server::Response::Response> r(
            std::move(m_responses.front())
        );
        m_responses.pop();
        return r;
    }
    return nullptr; // no response
}

} // namespace Connector

#pragma once

#include <map>
#include <string>

#include "server/map_state.hpp"

namespace Graphics {
class Living;
} // namespace Graphics

using GraphicLivingsMap =
    std::map<std::string, std::unique_ptr<Graphics::Living>>;

class LocalMapState : public Dummy::Server::MapState {
public:
    LocalMapState();
    void visitMapUpdate(
        const Dummy::Protocol::MapUpdate::CharacterPosition&
    ) override;

    void visitMapUpdate(
        const Dummy::Protocol::MapUpdate::CharacterOff&
    ) override;

    void visitMapUpdate(
        const Dummy::Protocol::MapUpdate::CharacterOn&
    ) override;
private:
    GraphicLivingsMap m_graphicLivingsMap;
};

#include "client.hpp"
#include "graphics/player.hpp"

namespace Graphics {

Player::Player(::Client& client,
               const std::string& chipset,
               const std::string& name,
               std::size_t x, std::size_t y,
               Direction direction)
    : Living(chipset, name, 24, 32, x, y, direction), m_client(client)
{

}

} // namespace Graphics

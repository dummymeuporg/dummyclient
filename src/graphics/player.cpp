#include "client.hpp"
#include "graphics/player.hpp"

namespace Graphics {

Player::Player(::Client& client,
               const std::string& chipset,
               std::size_t x, std::size_t y)
    : Living(chipset, 24, 32, x, y), m_client(client)
{

}

} // namespace Graphics

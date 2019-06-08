#include "client.hpp"
#include "map_view.hpp"
#include "graphics/player.hpp"

namespace Graphics {

Player::Player(const ::MapView& mapView,
               ::Client& client,
               const std::string& chipset,
               const std::string& name,
               std::size_t x, std::size_t y,
               std::size_t scaleFactor,
               Direction direction)
    : Living(mapView, chipset, name, 24, 32, x, y, scaleFactor, direction),
      m_client(client)
{

}

} // namespace Graphics

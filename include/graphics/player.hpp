#include "graphics/living.hpp"

class Client;
class MapView;

namespace Graphics {

class Player : public Living {
public:
    Player(
        const ::MapView&,
        ::Client&,
        const std::string&,
        const std::string&,
        std::size_t,
        std::size_t,
        std::size_t,
        Direction direction = Direction::DOWN
    );
protected:
    ::Client& m_client;
};

} // namespace Graphics

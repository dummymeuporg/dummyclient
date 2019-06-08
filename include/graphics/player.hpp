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

    virtual void tick() override;
protected:
    void _move(int, int);

    std::pair<std::uint16_t, std::uint16_t> _translateCoordsToServ(
        std::uint16_t,
        std::uint16_t
    );
    ::Client& m_client;
};

} // namespace Graphics

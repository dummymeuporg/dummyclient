#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "game.hpp"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <account> <session_id> "
            << std::endl;
        exit(EXIT_FAILURE);
    }
    Game game(argv[1], argv[2]);

    return game.run();
}


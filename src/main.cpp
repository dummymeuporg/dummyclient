#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "client.hpp"
#include "screen/select_character_screen.hpp"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <account> <session_id> "
            << std::endl;
        exit(EXIT_FAILURE);
    }
    Credentials credentials(argv[1], argv[2]);
    sf::RenderWindow window(sf::VideoMode(1024, 768), "DummyClient");
    Client client(credentials);
    std::shared_ptr<Screen::SelectCharacterScreen> screen(
        new Screen::SelectCharacterScreen(window, client)
    );
    client.setScreen(screen);
    client.connect("localhost", 6612);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        client.checkData();
        window.clear();
        client.screen()->draw();
        window.display();
    }

    return EXIT_SUCCESS;
}


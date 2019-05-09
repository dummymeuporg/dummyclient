#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "client.hpp"

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
    client.connect("localhost", 6612);
    client.authenticate();
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
        window.display();
    }

    return EXIT_SUCCESS;
}


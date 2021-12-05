#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cluster.h"

#if defined (_DEBUG)
#pragma comment (lib, "sfml-window-d.lib")
#pragma comment (lib, "sfml-graphics-d.lib")
#pragma comment (lib, "sfml-system-d.lib")
#else
#pragma comment (lib, "sfml-window.lib")
#pragma comment (lib, "sfml-graphics.lib")
#pragma comment (lib, "sfml-system.lib")
#endif 

constexpr int Width = 800;
constexpr int Height = 800;
constexpr int FramerateLimit = 60;

int main()
{
    Cluster cluster(4);

    sf::RenderWindow window(sf::VideoMode(Width, Height), "Cluster", sf::Style::Close);
    window.setFramerateLimit(FramerateLimit);

    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        cluster.Update();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}
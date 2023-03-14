#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "Quadtree! plus boids later :)");

    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(0.f, 0.f)),
        sf::Vertex(sf::Vector2f(150.f, 150.f))
    };

    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(line, 2, sf::Lines);
        window.display();
    }

    return 0;
}
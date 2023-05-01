#include <iostream>
#include <SFML/Graphics.hpp>
#include "QuadTree.h"

int main()
{
    float width = 600;
    float height = 400;
    
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(width), static_cast<unsigned int>(height)), "Quadtree! plus boids later :)");

    Point screenCenter;
    screenCenter.x = width / 2;
    screenCenter.y = height / 2;
    
    AABB screen;
    screen.center = screenCenter;
    screen.halfWidth = width / 2;
    screen.halfHeight = height / 2;

    QuadTree* tree = new QuadTree(screen, 4);
    
    for (int i = 0; i < 1000; i++)
    {
        Point point;
        point.x = std::rand() % static_cast<int>(width);
        point.y = std::rand() % static_cast<int>(height);

        tree->Insert(point);
    }

    std::vector<Point> points = tree->QueryRange(screen);

    std::vector<AABB> boundaries = tree->GetBoundaries();
    
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

        //std::vector<Point> points = tree->QueryRange(screen);

        sf::Color color = sf::Color::Green;
        
        for (auto boundary : boundaries)
        {
            sf::Vertex topLine[] =
            {
                sf::Vertex(sf::Vector2f(boundary.center.x - boundary.halfWidth, boundary.center.y - boundary.halfHeight), color),
                sf::Vertex(sf::Vector2f(boundary.center.x + boundary.halfWidth, boundary.center.y - boundary.halfHeight), color)
            };

            window.draw(topLine, 2, sf::Lines);

            sf::Vertex botLine[] =
            {
                sf::Vertex(sf::Vector2f(boundary.center.x - boundary.halfWidth, boundary.center.y + boundary.halfHeight), color),
                sf::Vertex(sf::Vector2f(boundary.center.x + boundary.halfWidth, boundary.center.y + boundary.halfHeight), color)
            };

            window.draw(botLine, 2, sf::Lines);
            
            sf::Vertex leftLine[] =
            {
                sf::Vertex(sf::Vector2f(boundary.center.x - boundary.halfWidth, boundary.center.y + boundary.halfHeight), color),
                sf::Vertex(sf::Vector2f(boundary.center.x - boundary.halfWidth, boundary.center.y - boundary.halfHeight), color)
            };

            window.draw(leftLine, 2, sf::Lines);
            
            sf::Vertex rightLine[] =
            {
                sf::Vertex(sf::Vector2f(boundary.center.x + boundary.halfWidth, boundary.center.y + boundary.halfHeight), color),
                sf::Vertex(sf::Vector2f(boundary.center.x + boundary.halfWidth, boundary.center.y - boundary.halfHeight), color)
            };

            window.draw(rightLine, 2, sf::Lines);
        }
        
        for (auto point : points)
        {
            sf::CircleShape circle(0.3f);
            circle.setPosition(sf::Vector2f(point.x, point.y));
            window.draw(circle);
        }
        
        window.display();
    }

    return 0;
}
#include "Application.h"

Application::Application()
{
    
}

Application::~Application()
{
    
}

void Application::Run()
{
    float width = 1920;
    float height = 1080;
    
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(width), static_cast<unsigned int>(height)), "Quadtree! plus boids later :)");

    Point screenCenter{};
    screenCenter.x = width / 2;
    screenCenter.y = height / 2;
    
    AABB screen{};
    screen.center = screenCenter;
    screen.halfWidth = width / 2;
    screen.halfHeight = height / 2;

    QuadTree* tree = new QuadTree(screen, 4);

    std::vector<Boid*> boids;
    
    for (int i = 0; i < 500; ++i)
    {
        Boid* boid = new Boid;
        boid->SetPosition(std::rand() % static_cast<int>(width), std::rand() % static_cast<int>(height));
        boids.push_back(boid);
    }

    std::vector<Boid*> boidsInScreen;

    std::vector<Boid*> boidsInRange;
    
    std::vector<AABB> boundaries;
    
    while(window.isOpen())
    {
        boidsInScreen.clear();
        boundaries.clear();
        
        tree = new QuadTree(screen, 4);

        for (auto& boid : boids)
        {
            tree->Insert(boid);
        }

        boidsInScreen = tree->QueryRange(screen);
        boundaries = tree->GetBoundaries();
        boidsInRange.clear();

        AABB mouseRange{};
        Point p{};
        p.x = sf::Mouse::getPosition(window).x;
        p.y = sf::Mouse::getPosition(window).y;
        mouseRange.center = p;
        mouseRange.halfWidth = 50;
        mouseRange.halfHeight = 50;
        
        boidsInRange = tree->QueryRange(mouseRange);
        
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();

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
        int i = 0;
        for (auto& boid : boids)
        {
            AABB boidRange{};
            boidRange.center = boid->GetPosition();
            boidRange.halfWidth = 50;
            boidRange.halfHeight = 50;
            
            boid->Flock(tree->QueryRange(boidRange));
            
            sf::CircleShape circle(3.f);
            circle.setFillColor(sf::Color(255, 255, 255));
            circle.setPosition(sf::Vector2f(boid->GetPosition().x, boid->GetPosition().y));
            window.draw(circle);
            i++;
        }
        
        window.display();

        delete tree;
    }
}



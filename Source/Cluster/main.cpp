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

class EventEntity
{
public:

};

class EventComponent : public Cluster::Component<EventEntity>
{
    void Update(int index, float deltaTime) override
    {

    }
};

class GameObjectEntity
{
public:
    Vector3 position;
};

class GameObjectComponent : public Cluster::Component<GameObjectEntity>
{
    //GameObjectComponent(Cluster& cluster) : Cluster::Component<GameObjectEntity>(cluster) {}

    void Update(int index, float deltaTime) override
    {
        entities[index].position.x++;
    }
};

class TestEntity
{
public:

};

class TestComponent : public Cluster::Component<TestEntity>
{
public:
    void Update(int index, float deltaTime) override
    {

    }
};

int main()
{
    Cluster cluster(4);

    cluster.AddComponent<GameObjectComponent>();
    

    //sf::RenderWindow window(sf::VideoMode(Width, Height), "Cluster", sf::Style::Close);
    //window.setFramerateLimit(FramerateLimit);

    //while (window.isOpen())
    //{
    //    sf::Event e;
    //    while (window.pollEvent(e))
    //    {
    //        if (e.type == sf::Event::Closed)
    //            window.close();
    //    }

    //    cluster.Update();

    //    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    //    window.clear(sf::Color::Black);
    //    window.display();
    //}

    return 0;
}
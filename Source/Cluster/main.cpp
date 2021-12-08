#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cluster.h"
#include <thread>

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

using Vector3 = sf::Vector3<float>;

class EventEntity
{
public:

};

class EventComponent : public Cluster::Node::Component<EventEntity>
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

class GameObjectComponent : public Cluster::Node::Component<GameObjectEntity>
{
    void Update(int index, float deltaTime) override
    {
        if (auto eventComponent = GetComponent<EventComponent>().lock())
        {
            eventComponent->GetEntity(index);
        }
        GetEntity(index).position.x++;
    }
};

class TestEntity
{
public:

};

class TestComponent : public Cluster::Node::Component<TestEntity>
{
public:
    void Update(int index, float deltaTime) override
    {

    }
};

int main()
{
    auto node = std::make_shared<Cluster::Node>();
    node->AddComponent<EventComponent>();
    node->AddComponent<GameObjectComponent>();

    auto cluster = std::make_shared<Cluster>();
    cluster->AddNode(node);

    for (;;)
    {
        cluster->Update(1.0f);// 나중에 수정
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
    }

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
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
using Vector2 = sf::Vector2<float>;

class EventEntity : public Cluster::BaseEntity
{
public:

};

class EventComponent : public Cluster::Node::Component<EventEntity>
{
    void Update(int index, float deltaTime) override
    {

    }
};

class GameObjectEntity : public Cluster::BaseEntity
{
public:
    Vector3 position;
    float radius;
};

class GameObjectComponent : public Cluster::Node::Component<GameObjectEntity>
{
    void Update(int index, float deltaTime) override
    {
        if (auto eventComponent = GetComponent<EventComponent>().lock())
        {
            auto& entity = eventComponent->GetEntity(index);
        }
        GetEntity(index).position.x++;
    }

    void Draw(int index, sf::RenderWindow& window) override
    {
        const auto& entity = GetEntity(index);
        sf::CircleShape shape(entity.radius);
        shape.setFillColor(sf::Color::Cyan);
        shape.setPosition(entity.position.x - entity.radius, entity.position.y - entity.radius);
    }
};

class TestEntity : public Cluster::BaseEntity
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

    sf::View view(sf::FloatRect(Width * -0.5f, -Height * -0.5f, Width, Height));

    sf::RenderWindow window(sf::VideoMode(Width, Height), "Cluster", sf::Style::Close);
    window.setFramerateLimit(FramerateLimit);
    window.setView(view);

    std::chrono::system_clock::time_point updateTime = std::chrono::system_clock::now();

    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        auto deltaTime = std::chrono::duration<float>(std::chrono::system_clock::now() - updateTime).count();
        updateTime = std::chrono::system_clock::now();
        cluster->Update(deltaTime);

        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        window.clear(sf::Color::Black);
        cluster->Draw(window);// Draw는 일단 싱글 스레드
        window.display();
    }

    return 0;
}
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

class EventComponent : public Cluster::Node::Component
{
public:
    void Update(float deltaTime) override
    {

    }

    void DoSomeThing()
    {

    }
    
    void Initialize(void* parameter)
    {

    }
};

class GameObjectComponent : public Cluster::Node::Component
{
public:
    void Update(float deltaTime) override
    {
        if (auto eventComponent = GetComponent<EventComponent>().lock())
        {
            eventComponent->DoSomeThing();
        }
        position.x++;
    }

    void Draw(sf::RenderWindow& window) override
    {
        sf::CircleShape shape(radius);
        shape.setFillColor(sf::Color::Cyan);
        shape.setPosition(position.x - radius, position.y - radius);
    }

    void Initialize(void* parameter)
    {

    }

private:
    Vector3 position;
    float radius;
};

class TestComponent : public Cluster::Node::Component
{
public:
    void Update(float deltaTime) override
    {

    }
};

int main()
{
    auto node = std::make_shared<Cluster::Node>();
    node->AddComponent<EventComponent>();
    node->AddComponent<GameObjectComponent>();

    auto cluster = std::make_shared<Cluster>();
    cluster->AddNode(std::static_pointer_cast<Cluster::INode>(node));

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
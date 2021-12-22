#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cluster.h"
#include <thread>
#include <random>

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

class BallParameter
{
public:
    float radius;
    Vector3 position;
    sf::Color color;
};

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
        auto param = static_cast<BallParameter*>(parameter);


    }
};

class GameObjectComponent : public Cluster::Node::Component
{
public:
    void Update(float deltaTime) override
    {
        //if (auto eventComponent = GetComponent<EventComponent>().lock())
        //{
        //    eventComponent->DoSomeThing();
        //}
        position.x += 100 * deltaTime;
    }

    void Draw(sf::RenderWindow& window) override
    {
        sf::CircleShape shape(radius);
        shape.setFillColor(color);
        shape.setPosition(position.x - radius, position.y - radius);
        window.draw(shape);
    }

    void Initialize(void* parameter)
    {
        auto param = static_cast<BallParameter*>(parameter);

        this->radius = param->radius;
        this->position = param->position;
        this->color = param->color;
    }

private:
    Vector3 position;
    float radius;
    sf::Color color;
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
    auto ballNode = std::make_shared<Cluster::Node>();
    ballNode->AddComponent<EventComponent>();
    ballNode->AddComponent<GameObjectComponent>();

    auto cluster = std::make_shared<Cluster>();
    cluster->AddNode(std::static_pointer_cast<Cluster::INode>(ballNode));

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> posGen(-400, 400);
    std::uniform_real_distribution<float> radGen(5, 30);
    std::uniform_int_distribution<int> colorGen(1, 255);

    for (int i = 0; i < 10; i++)
    {
        BallParameter param;
        param.radius = radGen(gen);
        param.position = Vector3(posGen(gen), posGen(gen), 0.0f);
        param.color = sf::Color(colorGen(gen), colorGen(gen), colorGen(gen), colorGen(gen));
        ballNode->AddObject(&param);
    }

    sf::View view(sf::FloatRect(Width * -0.5f, Height * -0.5f, Width, Height));

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

        window.clear(sf::Color::White);
        cluster->Draw(window);// Draw는 일단 싱글 스레드
        window.display();
    }

    return 0;
}
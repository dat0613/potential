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

class BallParameter
{
public:
    float radius;
    Vector3 position;
    sf::Color color;
};

class RectangleParameter
{
public:
    Vector2 size;
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

class BallComponent : public Cluster::Node::Component
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
        shape.setPosition(position.x - radius, position.y - radius);
        window.draw(shape);
    }

    void Initialize(void* parameter)
    {
        auto param = static_cast<BallParameter*>(parameter);

        this->radius = param->radius;
        this->position = param->position;
        this->color = param->color;

        shape.setRadius(radius);
        shape.setFillColor(color);
    }

private:
    sf::CircleShape shape;
    Vector3 position;
    float radius;
    sf::Color color;
};

class RectangleComponent : public Cluster::Node::Component
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
        shape.setPosition(position.x - size.x * 0.5f, position.y - size.y * 0.5f);
        window.draw(shape);
    }

    void Initialize(void* parameter)
    {
        auto param = static_cast<RectangleParameter*>(parameter);

        this->size = param->size;
        this->position = param->position;
        this->color = param->color;

        shape.setSize(param->size);
        shape.setFillColor(color);
    }

private:
    sf::RectangleShape shape;
    Vector3 position;
    Vector2 size;
    sf::Color color;
};

class TestComponent : public Cluster::Node::Component
{
public:
    void Update(float deltaTime) override
    {

    }
};

void CreateBallNode(std::shared_ptr<Cluster::Node>& ballNode)
{
    ballNode->AddComponent<EventComponent>();
    ballNode->AddComponent<BallComponent>();

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
}

void CreateRectangleNode(std::shared_ptr<Cluster::Node>& ballNode)
{
    ballNode->AddComponent<EventComponent>();
    ballNode->AddComponent<RectangleComponent>();

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> posGen(-400, 400);
    std::uniform_real_distribution<float> sizeGen(5, 30);
    std::uniform_int_distribution<int> colorGen(1, 255);

    for (int i = 0; i < 10; i++)
    {
        RectangleParameter param;
        param.size = Vector2(sizeGen(gen), sizeGen(gen));
        param.position = Vector3(posGen(gen), posGen(gen), 0.0f);
        param.color = sf::Color(colorGen(gen), colorGen(gen), colorGen(gen), colorGen(gen));
        ballNode->AddObject(&param);
    }
}

int main()
{
    auto ballNode = std::make_shared<Cluster::Node>();
    CreateBallNode(ballNode);

    auto rectNode = std::make_shared<Cluster::Node>();
    CreateRectangleNode(rectNode);

    auto cluster = std::make_shared<Cluster>();
    cluster->AddNode(std::static_pointer_cast<Cluster::INode>(ballNode));
    cluster->AddNode(std::static_pointer_cast<Cluster::INode>(rectNode));

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
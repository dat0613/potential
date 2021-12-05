#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

using Vector3 = sf::Vector3<float>;

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
	Vector3 position;

	void Update() {};

};


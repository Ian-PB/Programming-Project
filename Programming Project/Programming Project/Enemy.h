#pragma once

#include <SFML/Graphics.hpp>

class Enemy
{
public:

	void moveToTarget(sf::Vector2f t_targetPos);
	void setup(sf::Vector2f t_pos);

	sf::CircleShape getBody() { return body; }

private:

	sf::CircleShape body;
	sf::Vector2f position;
	float size = 10.0f;

	int speed = 1;
	sf::Vector2f velocity;


};


#pragma once

#include <SFML/Graphics.hpp>

#include "Globals.h"

class Partical
{
public:

	Partical();

	void setup();
	sf::RectangleShape getBody() { return body; }
	sf::Sprite getSprite() { return sprite; }

	void spawn(sf::Vector2f t_pos);

	void move();

	void bounds();

	bool active = false;

private:

	sf::RectangleShape body;
	float size = 10;
	const int MIN_SIZE = 5;

	sf::Texture texture;
	sf::Sprite sprite;

	sf::Vector2f position;
	int speed = 0;
	const int MIN_SPEED = 2;

	float angle = 0.0f;
	sf::Vector2f direction;
};


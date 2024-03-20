#pragma once

#include <SFML/Graphics.hpp>


enum class Direction
{
	None,
	Up,
	Down,
	Left,
	Right
};

class Player
{

public:

	Player();

	// Movement
	void checkDirection();
	void rotateToMouse(sf::Vector2f t_mousePos);

	void setup(sf::Vector2f t_pos);

	// "Get" functions
	sf::RectangleShape getBody() { return body; }

private:

	// Functions
	void checkBoundries();
	void move();

	// Variables
	sf::RectangleShape body;
	float size = 50.0f;
	sf::Vector2f position;

	bool alive = true;

	// Movement Variables
	float speed = 5.0f;
	Direction direction;

};


#pragma once

#include <SFML/Graphics.hpp>

class Platform
{
public:
	Platform();

	void setup(sf::Vector2f t_pos);
	sf::RectangleShape getBody() { return body; }
	sf::RectangleShape getGround() { return ground; }

private:

	// Body
	sf::RectangleShape body;
	float width = 200;
	float height = 20;
	sf::Vector2f position;

	sf::RectangleShape ground; // { Same width, 1.0f }
	const sf::Vector2f GROUND_DISPLACEMENT = { 0.0f, -15 };


};


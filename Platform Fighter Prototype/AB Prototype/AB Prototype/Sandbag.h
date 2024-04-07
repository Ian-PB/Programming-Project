#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include <iostream>

class Sandbag
{
public:
	Sandbag();
	void setup(sf::Vector2f t_pos);
	void setupIndicator();

	// "Get" Functions
	sf::RectangleShape getBody() { return body; }
	sf::CircleShape getIndicatorBody() { return indicator; }

	void gravity();
	void checkBoundries();

	void takeDamage(int t_damage);

	void knockback(int t_angleD, float& t_power, int t_damage);
	int bounce(float t_angleD);

	void offScreenIndicator();

	bool hitAgain = false;
	bool knockingBack = false;

	// Off screen Indicator
	bool indicatorActive = false;

	int percentage = 0;

private:

	sf::RectangleShape body;
	float height = 100;
	float width = 50;

	sf::Vector2f position;

	float deceleration = 0;
	const float POWER_GRAVITY_MULTIPLIER = 1.5f;
	const float PERCENTAGE_DIVIDER = 10.0f;

	sf::Vector2f direction;

	float totalDuration = 0.0f;

	// Off screen Indicator
	sf::CircleShape indicator;
	float indicatorRadius = 20;
	sf::Vector2f indicatorPos = {0.0f, 25.0f};
};


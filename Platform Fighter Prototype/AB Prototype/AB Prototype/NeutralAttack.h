#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Sandbag.h"

class NeutralAttack
{
public:

	NeutralAttack();

	// "Get" Functions
	sf::RectangleShape getBodyLeft() { return hitboxLeft; }
	sf::RectangleShape getBodyRight() { return hitboxRight; }

	void spawn(sf::Vector2f t_pos);
	void attack(sf::Vector2f t_pos, Sandbag& t_sandbag, bool& t_canAttack);
	bool active = false;

	// Information of the attack for the sandbag
	int damage = 3; // Damage done
	const int END_LAG = 0.2f * 60; // Delay before you can attack again
	float power = 3; // How fast it's knocked back

	float angleD; // 0 is straight up, 45 ->, 180 down, 315 <-
	
	bool hasHit = false;


private:

	void setup();

	// Hitbox
	sf::RectangleShape hitboxLeft;
	sf::RectangleShape hitboxRight;
	float width = 5.0f;
	float height = 100.0f;
	sf::Vector2f positionLeft;
	sf::Vector2f positionRight;
	const sf::Vector2f DISPLACEMENT_LEFT = { -25.0f, 0.0f };
	const sf::Vector2f DISPLACEMENT_RIGHT = { 25.0f, 0.0f };

	// Directions possible
	float angleDRight = 10; // 0 is straight up, 45 ->, 180 down, 315 <-
	float angleDLeft = 360 - (angleDRight * 1.5f); // 0 is straight up, 45 ->, 180 down, 315 <-


	// Information of attacks
	int timer = 0;
	const int ACTIVE_DURATION = 0.2f * 60; // Seconds wanted * Framerate
};


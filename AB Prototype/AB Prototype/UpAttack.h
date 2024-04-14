#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Sandbag.h"

class UpAttack
{
public:

	UpAttack();

	// "Get" Functions
	sf::RectangleShape getBody() { return hitbox; }

	void spawn(sf::Vector2f t_pos);
	void attack(sf::Vector2f t_pos, Sandbag& t_sandbag, bool& t_canAttack);
	bool active = false;

	// Information of the attack for the sandbag
	int damage = 6; // Damage done
	const int END_LAG = 0.2f * 60; // Delay before you can attack again
	float angleD = 0; // 0 is straight up, 45 ->, 180 down, 315 <-
	float power = 4; // How fast it's knocked back
	bool knockingBack = false;

	bool hasHit = false;


private:

	void setup();

	// Hitbox
	sf::RectangleShape hitbox;
	float width = 60.0f;
	float height = 30.0f;
	sf::Vector2f position;
	const sf::Vector2f DISPLACEMENT = { 0.0f, -50.0f };


	// Information of attacks
	int timer = 0;
	const int ACTIVE_DURATION = 0.2f * 60; // Seconds wanted * Framerate
};


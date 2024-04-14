#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Sandbag.h"

class SideAttack
{
public:
	SideAttack();

	void setup(bool t_leftAttack);

	// "Get" Functions
	sf::RectangleShape getBody() { return hitbox; }

	void spawn(sf::Vector2f t_pos);
	void attack(sf::Vector2f t_pos, Sandbag& t_sandbag, bool& t_canAttack);
	bool active = false;

	// Information of the attack for the sandbag
	int damage = 5; // Damage done
	const int END_LAG = 0.4f * 60; // Delay before you can attack again
	float angleD; // 0 is straight up, 45 ->, 180 down, 315 <-
	float power = 0.1f; // How fast it's knocked back
	bool knockingBack = false;

	bool hasHit = false;


private:

	// Hitbox
	sf::RectangleShape hitbox;
	float width = 40.0f;
	float height = 80.0f;
	sf::Vector2f position;
	sf::Vector2f displacement = { 0.0f, 0.0f };

	// Left or Right
	float angleRight = 85.0f; // 0 is straight up, 45 ->, 180 down, 315 <-
	float angleLeft; // 0 is straight up, 45 ->, 180 down, 315 <-


	// Information of attacks
	bool leftAttack = true;
	int timer = 0;
	const int ACTIVE_DURATION = 0.2f * 60; // Seconds wanted * Framerate
};


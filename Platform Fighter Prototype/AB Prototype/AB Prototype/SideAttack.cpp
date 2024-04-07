#include "SideAttack.h"



SideAttack::SideAttack()
{
	if (angleRight > 225 && angleRight <= 225)
	{
		angleLeft = 360 - (angleRight * 1.5f);
	}
	else
	{
		angleLeft = 360 - angleRight;
	}
}

void SideAttack::setup(bool t_leftAttack)
{
	// Check what direction the side attack is in
	leftAttack = t_leftAttack;
	// If attacking to the left...
	if (leftAttack)
	{
		displacement = { -15.0f, 0.0f };
		angleD = angleLeft;
	}
	// If attacking to the right
	else
	{
		displacement = { 15.0f, 0.0f };
		angleD = angleRight;
	}

	hitbox.setFillColor(sf::Color::Green);
	hitbox.setSize({ width, height });
	hitbox.setOrigin({ width / 2, height / 2 });
}

void SideAttack::spawn(sf::Vector2f t_pos)
{
	// set the position
	position = t_pos;
	hitbox.setPosition(position);

	// set it to active
	active = true;
}

void SideAttack::attack(sf::Vector2f t_pos, Sandbag& t_sandbag, bool& t_canAttack)
{
	// While attack is happening
	if (timer < ACTIVE_DURATION)
	{
		timer++;

		// set the position
		position = t_pos;
		hitbox.setPosition(position + displacement);

		// if the hitbox intersects sandbag
		if (hitbox.getGlobalBounds().intersects(t_sandbag.getBody().getGlobalBounds()))
		{
			hasHit = true;
		}
		else
		{
			hasHit = false;
		}
	}
	// If the attack is over
	else if (timer >= ACTIVE_DURATION)
	{
		// Once the attack is over
		timer = 0;
		active = false;

		// Can attack becomes false
		t_canAttack = false;
	}
}

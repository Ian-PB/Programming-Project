#include "UpAttack.h"

UpAttack::UpAttack()
{
	setup();
}

void UpAttack::setup()
{
	hitbox.setFillColor(sf::Color::Green);
	hitbox.setSize({ width, height });
	hitbox.setOrigin({ width / 2, height / 2 });
}

void UpAttack::spawn(sf::Vector2f t_pos)
{
	// set the position
	position = t_pos;
	hitbox.setPosition(position);

	// set it to active
	active = true;
}

void UpAttack::attack(sf::Vector2f t_pos, Sandbag& t_sandbag, bool& t_canAttack)
{
	// While attack is happening
	if (timer < ACTIVE_DURATION)
	{
		timer++;

		// set the position
		position = t_pos;
		hitbox.setPosition(position + DISPLACEMENT);

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

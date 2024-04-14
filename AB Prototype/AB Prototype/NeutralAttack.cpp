#include "NeutralAttack.h"

NeutralAttack::NeutralAttack()
{
	setup();
}

void NeutralAttack::setup()
{
	// Left hitbox
	hitboxLeft.setFillColor(sf::Color::Green);
	hitboxLeft.setSize({ width, height });
	hitboxLeft.setOrigin({ width / 2, height / 2 });

	// Right hitbox
	hitboxRight.setFillColor(sf::Color::Magenta);
	hitboxRight.setSize({ width, height });
	hitboxRight.setOrigin({ width / 2, height / 2 });
}

void NeutralAttack::spawn(sf::Vector2f t_pos)
{
	// Set the position of left hitbox
	positionLeft = t_pos;
	hitboxLeft.setPosition(positionLeft + DISPLACEMENT_LEFT);

	// Set the position of right hitbox
	positionRight = t_pos;
	hitboxRight.setPosition(positionRight + DISPLACEMENT_RIGHT);

	// Set it to active
	active = true;
}

void NeutralAttack::attack(sf::Vector2f t_pos, Sandbag& t_sandbag, bool& t_canAttack)
{
	// While attack is happening
	if (timer < ACTIVE_DURATION)
	{
		timer++;

		// Set the position of Left hitbox
		positionLeft = t_pos;
		hitboxLeft.setPosition(positionLeft + DISPLACEMENT_LEFT);

		// Set the position of Right hitbox
		positionRight = t_pos;
		hitboxRight.setPosition(positionRight + DISPLACEMENT_RIGHT);


		// If the hitboxs intersects sandbag
		if (hitboxLeft.getGlobalBounds().intersects(t_sandbag.getBody().getGlobalBounds()))
		{
			angleD = angleDLeft;
			hasHit = true;
		}
		else if (hitboxRight.getGlobalBounds().intersects(t_sandbag.getBody().getGlobalBounds()))
		{
			angleD = angleDRight;
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

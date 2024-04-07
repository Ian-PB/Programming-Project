#include "Sandbag.h"

Sandbag::Sandbag()
{
	setupIndicator();
}

void Sandbag::setup(sf::Vector2f t_pos)
{
	position = t_pos;
	body.setPosition(position);

	body.setFillColor(sf::Color::Red);
	body.setSize({ width, height });
	body.setOrigin({ width / 2, height / 2 });
}

void Sandbag::setupIndicator()
{
	indicator.setFillColor(sf::Color::Red);
	indicator.setRadius( indicatorRadius );
	indicator.setOrigin({ indicatorRadius, indicatorRadius });
}

void Sandbag::gravity()
{
	position.y += GRAVITY;
	body.setPosition(position);
}

void Sandbag::checkBoundries()
{
	// x-axis checking
	if (position.x <= width / 2)
	{
		position.x = width / 2;
	}
	else if (position.x >= SCREEN_WIDTH - width / 2)
	{
		position.x = SCREEN_WIDTH - width / 2;
	}

	// y-axis checking
	if (position.y >= SCREEN_HEIGHT - (height / 2))
	{
		position.y = SCREEN_HEIGHT - (height / 2);
	}
}

void Sandbag::takeDamage(int t_damage)
{
	percentage += t_damage;
}

void Sandbag::knockback(int t_angleD, float& t_power, int t_damage)
{

	// Change the angle to Radians
	float angleR = (t_angleD) * 3.14f / 180;

	// FIND A WAY TO CHECK IF IT WAS HIT AGAIN
	// IF SO RESET DECELERATION
	if (hitAgain)
	{
		deceleration = 0;
		hitAgain = false; // So it only happens once
	}

	// Hit with deceleration
	if (knockingBack)
	{
		// Decelerate the knockback
		deceleration += 0.25f;

		direction.x = (sin(angleR) * ((t_power + (GRAVITY * POWER_GRAVITY_MULTIPLIER) + (percentage / PERCENTAGE_DIVIDER)) - deceleration));
		direction.y = (cos(angleR) * ((t_power + (GRAVITY * POWER_GRAVITY_MULTIPLIER) + (percentage / PERCENTAGE_DIVIDER)) - deceleration)) * -1;
	}

	if (deceleration >= t_power + (GRAVITY * POWER_GRAVITY_MULTIPLIER) + (percentage / PERCENTAGE_DIVIDER))
	{
		// Reset
		deceleration = 0;

		t_power = 0.0f;

		knockingBack = false;
	}

	// set the position with the direction added
	position += direction;
	body.setPosition(position);
}

int Sandbag::bounce(float t_angleD)
{
	// x-axis checking
	if (position.x <= width / 2)
	{
		direction.x *= -1;
		t_angleD = 360 - t_angleD;
	}
	else if (position.x >= SCREEN_WIDTH - width / 2)
	{
		direction.x *= -1;
		t_angleD = 360 - t_angleD;
	}

	// y-axis checking
	if (position.y >= SCREEN_HEIGHT - (height / 2))
	{
		// Invert the velocity
		direction.y *= -1;

		// Change the angle if it's going downward
		if (t_angleD == 180)
		{
			t_angleD = 0;
		}
		else if (t_angleD <= 180 && t_angleD > 45) // Does bouncing to the right
		{
			t_angleD = (360 - (t_angleD * 1.5f)) / 10;
		}
		else if (t_angleD > 180 && t_angleD < 225) // Does bouncing to the left
		{
			if (t_angleD >= 180 && t_angleD <= 195)
			{
				t_angleD = (360 - (t_angleD * 1.842f)) * -1;
			}
			else
			{
				t_angleD = (360 - (t_angleD * 1.842f));
			}
		}
		else if (t_angleD > 225 && t_angleD < 315) // Does bouncing to the left
		{
			t_angleD = (360 - (t_angleD * 1.5)) * -1;
		}
	}

	return t_angleD;
}

void Sandbag::offScreenIndicator()
{
	if (position.y < -height)
	{
		indicatorActive = true;

		indicatorPos.x = position.x;
		indicator.setPosition(indicatorPos);
	}
	else
	{
		indicatorActive = false;
	}
}


#include "Partical.h"
#include <iostream>

Partical::Partical()
{
	setup();
}

void Partical::setup()
{
	if (!texture.loadFromFile("ASSETS\\IMAGES\\Partical.png"))
	{
		std::cout << "problem loading cry texture" << std::endl;
	}


	sprite.setTexture(texture);
	sprite.setOrigin({194.5f, 215.5f});

	// body.setFillColor(sf::Color::White);
	body.setFillColor({200, 200, 200, 255});
}

void Partical::spawn(sf::Vector2f t_pos)
{
	// Set position
	position = t_pos;
	body.setPosition(position);
	sprite.setPosition(position);

	// Randomize angle particals go in
	float randDirection = rand() % 360;
	angle = randDirection + 90;

	// Randomize speed
	speed = (rand() % 20) + 5;

	// Set size and rotation
	int randAngleD = (rand() % 360) + 1;
	float randScale = ((rand() % 25) + 26) / 100.0f;
	float randSize = (rand() % 30) + 11;
	// Sprite
	sprite.setRotation(randAngleD);
	sprite.setScale({ randScale, randScale });
	// Body
	size = randSize;
	body.setSize({ size, size });
	body.setOrigin({ size / 2, size / 2 });
	body.setRotation(randAngleD);
	
	active = true;
}

void Partical::move()
{
	// 0 is Right, adding to 0 will make it go anti-clockwise
	float angleR = (angle) * 3.14f / 180;

	direction.x = (sin(angleR) * speed);
	direction.y = (cos(angleR) * speed) * -1;

	position += direction;


	// Decrease size as it moves
	if (size > MIN_SIZE)
	{
		size -= 0.2f;
		body.setSize({ size, size });
	}
	else
	{
		active = false;
	}
	// Decease Speed as it moves
	if (speed > MIN_SPEED)
	{
		speed -= 0.2f;
	}
	else
	{
		if (size > MIN_SIZE)
		{
			size -= 0.75f;
			body.setSize({ size, size });
		}
		else
		{
			active = false;
		}
	}

	body.setPosition(position);
	sprite.setPosition(position);
}

void Partical::bounds()
{
	if (position.x <= -50)
	{
		active = false;
	}
	else if (position.x >= SCREEN_WIDTH + 100)
	{
		active = false;
	}

	if (position.y <= -50)
	{
		active = false;
	}
	else if (position.y >= SCREEN_HEIGHT + 100)
	{
		active = false;
	}
}

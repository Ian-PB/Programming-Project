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

	body.setFillColor(sf::Color::White);
}

void Partical::spawn(sf::Vector2f t_pos)
{
	// Set position
	position = t_pos;
	body.setPosition(position);
	sprite.setPosition(position);

	// Randomize angle
	float randDirection = rand() % 360;
	angle = randDirection + 90;

	// Randomize speed
	speed = (rand() % 20) + 5;

	// Set size and rotation
	int randAngleD = (rand() % 360) + 1;
	float randScale = ((rand() % 25) + 26) / 100.0f;
	float randSize = (rand() % 40) + 11;
	// Sprite
	sprite.setRotation(randAngleD);
	sprite.setScale({ randScale, randScale });
	// Body
	body.setSize({ randSize, randSize });
	body.setOrigin({ randSize / 2, randSize / 2 });
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

	body.setPosition(position);
	sprite.setPosition(position);
}

void Partical::bounds()
{
	if (position.x <= -50)
	{
		active = false;
	}
	else if (position.x >= 900)
	{
		active = false;
	}

	if (position.y <= -50)
	{
		active = false;
	}
	else if (position.y >= 700)
	{
		active = false;
	}
}

#include "Platform.h"

Platform::Platform()
{
}

void Platform::setup(sf::Vector2f t_pos)
{
	position = t_pos;
	body.setPosition(position);
	body.setFillColor(sf::Color::Green);
	body.setSize({ width, height });
	body.setOrigin({ width / 2.0f, height / 2.0f });

	ground.setPosition(position + GROUND_DISPLACEMENT);
	ground.setFillColor(sf::Color::White);
	ground.setSize({ width, 10.0f });
	ground.setOrigin({ width / 2.0f, 0.5f });
}

#include "Enemy.h"

void Enemy::moveToTarget(sf::Vector2f t_targetPos)
{
	// Variables
	float lenght = 0.0f;
	sf::Vector2f heading(0.0f, 0.0f);

	heading.x = (t_targetPos.x) - position.x;
	heading.y = (t_targetPos.y) - position.y;
	lenght = sqrtf((heading.x * heading.x) + (heading.y * heading.y)); // find the distance

	heading = heading / lenght;
	heading.x *= speed; // change speed to the actual speed
	heading.y *= speed; // change speed to the actual speed
	velocity = heading;

	position += velocity;
	body.setPosition(position);
}

void Enemy::setup(sf::Vector2f t_pos)
{
	position = t_pos;

	body.setPosition(position);

	body.setFillColor(sf::Color::Red);
	body.setRadius(size);
	body.setOrigin({ size, size});
}

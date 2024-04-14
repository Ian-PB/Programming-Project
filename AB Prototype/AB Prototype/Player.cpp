#include "Player.h"


Player::Player()
{
}

void Player::setup(sf::Vector2f t_pos)
{
	position = t_pos;
	body.setPosition(position);

	body.setFillColor(sf::Color::Blue);
	body.setSize({ width, height });
	body.setOrigin({ width / 2, height / 2 });

	// Ground checker setup
	groundChecker.setPosition(position + GROUND_CHECK_DISPLACEMENT);
	groundChecker.setFillColor(sf::Color::White);
	groundChecker.setSize({ width, 1.0f });
	groundChecker.setOrigin({ width / 2, 0.5f });
}

void Player::move(Controller& t_controller, bool t_controllerConnected)
{
	if (t_controllerConnected)
	{

		// Left movement
		if (t_controller.currentState.LeftThumbStick.x < -25)
		{
			position.x += -speed;
		}

		// Right movement
		if (t_controller.currentState.LeftThumbStick.x > 25)
		{
			position.x += speed;
		}

		// Fast fall
		if (t_controller.currentState.LeftThumbStick.y > 50) // When S is held...
		{
			if (fastfallCounter < TIME_TILL_FASTFALL)
			{
				fastfallCounter++;
			}
			else if (fastfallCounter >= TIME_TILL_FASTFALL)
			{
				fastfall = true;
			}
		}
		else // When S is not held...
		{
			fastfall = false; // Stop fastfall
			fastfallCounter = 0; // Reset the counter
		}
	}
	else
	{
		// Left movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			position.x += -speed;
		}

		// Right movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			position.x += speed;
		}


		// Fast fall
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // When S is held...
		{
			if (fastfallCounter < TIME_TILL_FASTFALL)
			{
				fastfallCounter++;
			}
			else if (fastfallCounter >= TIME_TILL_FASTFALL)
			{
				fastfall = true;
			}
		}
		else // When S is not held...
		{
			fastfall = false; // Stop fastfall
			fastfallCounter = 0; // Reset the counter
		}
	}
}

void Player::jump()
{
	// If you don't have more jumps you can't jump
	if (jumpAmount <= 0)
	{
		canJump = false;
	}

	if (jumpAgain)
	{
		std::cout << jumpAmount << std::endl;
		jumpAmount--;

		deceleration = 0;
		jumpAgain = false;
	}

	if (jumpTimer <= RISE_DURATION)
	{
		position.y -= JUMP_FORCE + GRAVITY;

		jumpTimer++;
	}
	else if (jumpTimer >= RISE_DURATION) // Once done rising start decreasing the jump force
	{
		// This makes a nice arc on the jump
		deceleration += 0.5f;
		position.y -= (JUMP_FORCE + GRAVITY) - deceleration;

		jumpTimer++;
	}

	// Jump is done, once the deleceration is == to the jump force
	if (deceleration >= JUMP_FORCE + GRAVITY) 
	{
		deceleration = 0;
		jumpTimer = 0;
		jumping = false;
	}

	// Set position
	body.setPosition(position);
	groundChecker.setPosition(position + GROUND_CHECK_DISPLACEMENT);
}

// Needs to go through each platform and see if it intersects with the ground checker
void Player::groundCheck(Platform t_platform)
{

	if (groundChecker.getPosition().y >= SCREEN_HEIGHT)
	{
		onGround = true;
	}
	// Platform checking
	else if (groundChecker.getGlobalBounds().intersects(t_platform.getGround().getGlobalBounds()))
	{
		onGround = true;
	}
	else
	{
		onGround = false;
	}

	if (onGround && !jumping)
	{
		// Reset your jumps
		jumpAmount = MAX_JUMPS;

		// Since on the floor you can jump
		canJump = true;
	}
}

void Player::gravity()
{
	if (!onGround)
	{
		// While fastfalling use extra gravity
		if (fastfall)
		{
			position.y += FASTFALL_SPEED;
		}
		// While not fastfalling use normal gravity
		else
		{
			position.y += GRAVITY;
		}
	}

	body.setPosition(position);
	groundChecker.setPosition(position + GROUND_CHECK_DISPLACEMENT);
}

void Player::checkBoundries()
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
}

void Player::changeColor(bool t_canAttack)
{
	if (t_canAttack)
	{
		body.setFillColor(sf::Color::Blue);
	}
	else
	{
		body.setFillColor( {50, 50, 255, 125} );
	}
}

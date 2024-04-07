/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupObjects(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	controllerConnected = false;

	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}

	// Player's Jump
	if (sf::Keyboard::Space == t_event.key.code)
	{
		if (player.canJump)
		{
			player.jumping = true;
			player.jumpAgain = true;
		}
	}

	// If can attack...
	if (canAttack)
	{
		// If J is pressed and ...
		if (sf::Keyboard::J == t_event.key.code)
		{
			// Up Attack
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				upAttack.spawn(player.getPosition());
			}
			// Down Attack
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				downAttack.spawn(player.getPosition());
			}
			// Left Attack
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				sideAttackLeft.spawn(player.getPosition());
			}
			// Right Attack
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				sideAttackRight.spawn(player.getPosition());
			}
			else
			{
				neutralAttack.spawn(player.getPosition());
			}
		}
	}
}

void Game::processController()
{
	// Jumping
	if (controller.currentState.A)
	{
		if (!player.jumped)
		{
			if (player.canJump)
			{
				player.jumped = true;

				player.jumping = true;
				player.jumpAgain = true;
			}
		}
	}
	// Once let go allow another jump
	else
	{
		player.jumped = false;
	}
	

	// If can attack
	if (canAttack)
	{
		if (!buttonPressed)
		{
			// if X is pressed and ...
			if (controller.currentState.X)
			{
				// Up Attack
				if (controller.currentState.LeftThumbStick.y <= -50)
				{
					upAttack.spawn(player.getPosition());
				}
				// Down Attack
				else if (controller.currentState.LeftThumbStick.y >= 50)
				{
					downAttack.spawn(player.getPosition());
				}
				// Left Attack
				else if (controller.currentState.LeftThumbStick.x <= -50)
				{
					sideAttackLeft.spawn(player.getPosition());
				}
				// Right Attack
				else if (controller.currentState.LeftThumbStick.x >= 50)
				{
					sideAttackRight.spawn(player.getPosition());
				}
				else
				{
					neutralAttack.spawn(player.getPosition());
				}

				// Make sure only one attack is done at a time
				buttonPressed = true;
			}
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	if (controllerConnected)
	{
		controller.update();
		processController();
	}
	// Check if the controller should be connected
	else
	{
		controllerConnected = controller.connectCheck();
	}

	// Player
	player.move(controller, controllerConnected);
	// Jumping
	if (player.jumping)
	{
		player.jump();
	}

	player.groundCheck();
	player.gravity();
	player.checkBoundries();


	// Sandbag
	sandbag.gravity();
	sandbag.checkBoundries();
	// Off screen indicator
	sandbag.offScreenIndicator();

	/// Attack Knockback ///
	
	// Right Attack
	if (sideAttackRight.active) // Attack
	{
		sideAttackRight.attack(player.getPosition(), sandbag, canAttack);

		// Set the endlag
		endLagDuration = sideAttackRight.END_LAG;

		// If hit...
		if (sideAttackRight.hasHit)
		{
			knockbackAngle = sideAttackRight.angleD; // Set angle
			knockbackPower = sideAttackRight.power; // Set power
			damageTaken = sideAttackRight.damage; // Set the damage to add to sandbag's percentage


			sandbag.hitAgain = true;
			sandbag.knockingBack = true;


			// Do damage if damage has not been done
			if (!damageDone)
			{
				// Add to the sandbag's percentage
				sandbag.takeDamage(sideAttackRight.damage);
				

				damageDone = true;
			}
		}
	}

	// Left Attack
	if (sideAttackLeft.active) // Attack
	{
		sideAttackLeft.attack(player.getPosition(), sandbag, canAttack);

		// Set the endlag
		endLagDuration = sideAttackLeft.END_LAG;

		// If hit...
		if (sideAttackLeft.hasHit)
		{
			knockbackAngle = sideAttackLeft.angleD; // Set angle
			knockbackPower = sideAttackLeft.power; // Set power
			damageTaken = sideAttackLeft.damage; // Set the damage to add to sandbag's percentage


			sandbag.hitAgain = true;
			sandbag.knockingBack = true;


			// Do damage if damage has not been done
			if (!damageDone)
			{
				// Add to the sandbag's percentage
				sandbag.takeDamage(sideAttackLeft.damage);
				

				damageDone = true;
			}
		}
	}

	// Up Attack
	if (upAttack.active) // Attack
	{
		upAttack.attack(player.getPosition(), sandbag, canAttack);

		// Set the endlag
		endLagDuration = upAttack.END_LAG;

		// If hit...
		if (upAttack.hasHit)
		{
			knockbackAngle = upAttack.angleD; // Set angle
			knockbackPower = upAttack.power; // Set power
			damageTaken = upAttack.damage; // Set the damage to add to sandbag's percentage


			sandbag.hitAgain = true;
			sandbag.knockingBack = true;


			// Do damage if damage has not been done
			if (!damageDone)
			{
				// Add to the sandbag's percentage
				sandbag.takeDamage(upAttack.damage);
				

				damageDone = true;
			}
		}
	}

	// Down Attack
	if (downAttack.active) // Attack
	{
		downAttack.attack(player.getPosition(), sandbag, canAttack);

		// Set the endlag
		endLagDuration = downAttack.END_LAG;

		// If hit...
		if (downAttack.hasHit)
		{
			knockbackAngle = downAttack.angleD; // Set angle
			knockbackPower = downAttack.power; // Set power
			damageTaken = downAttack.damage; // Set the damage to add to sandbag's percentage


			sandbag.hitAgain = true;
			sandbag.knockingBack = true;


			// Do damage if damage has not been done
			if (!damageDone)
			{
				// Add to the sandbag's percentage
				sandbag.takeDamage(downAttack.damage);
				

				damageDone = true;
			}
		}
	}

	// Neutral Attack
	if (neutralAttack.active) // Attack
	{
		// Do the attack and check collisions
		neutralAttack.attack(player.getPosition(), sandbag, canAttack);

		// Set the endlag
		endLagDuration = neutralAttack.END_LAG;

		// If hit...
		if (neutralAttack.hasHit)
		{
			knockbackAngle = neutralAttack.angleD; // Set angle
			knockbackPower = neutralAttack.power; // Set power
			damageTaken = neutralAttack.damage; // Set the damage to add to sandbag's percentage


			sandbag.hitAgain = true;
			sandbag.knockingBack = true;

			// Do damage if damage has not been done
			if (!damageDone)
			{
				// Add to the sandbag's percentage
				sandbag.takeDamage(neutralAttack.damage);
				

				damageDone = true;
			}
		}
	}
	
	// Sandbags knockback
	if (sandbag.knockingBack)
	{
		// Change the percentage string
		sandbagPercentage.setString("Sandbag: " + std::to_string(sandbag.percentage) + "%");

		// Bouncing
		knockbackAngle = sandbag.bounce(knockbackAngle);
		sandbag.knockback(knockbackAngle, knockbackPower, damageTaken); // Knockback
	}

	if (!canAttack)
	{
		// Do endlag timer
		endLag();

		// Allow for another attack input from controller
		buttonPressed = false;

		// Allow damage again
		damageDone = false;
	}

	player.changeColor(canAttack);
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	
	// Sandbag
	m_window.draw(sandbag.getBody());
	// Off screen indicator
	if (sandbag.indicatorActive)
	{
		m_window.draw(sandbag.getIndicatorBody());
	}

	// Player
	m_window.draw(player.getBody());


	// Attacks
	if (downAttack.active)
	{
		m_window.draw(downAttack.getBody());
	}
	if (upAttack.active)
	{
		m_window.draw(upAttack.getBody());
	}
	if (sideAttackLeft.active)
	{
		m_window.draw(sideAttackLeft.getBody());
	}
	if (sideAttackRight.active)
	{
		m_window.draw(sideAttackRight.getBody());
	}
	if (neutralAttack.active)
	{
		m_window.draw(neutralAttack.getBodyLeft());
		m_window.draw(neutralAttack.getBodyRight());
	}

	// Sandbag's percentage
	m_window.draw(sandbagPercentage);

	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	sandbagPercentage.setFont(font);
	sandbagPercentage.setString("Sandbag: " + std::to_string(sandbag.percentage) + "%");
	sandbagPercentage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	sandbagPercentage.setCharacterSize(30U);
	sandbagPercentage.setOutlineColor(sf::Color::Red);
	sandbagPercentage.setFillColor(sf::Color::White);
	sandbagPercentage.setOutlineThickness(3.0f);

	sandbagPercentage.setPosition(SCREEN_WIDTH - 250, SCREEN_HEIGHT - 50);
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupObjects()
{
	// Player
	player.setup({ 300, 100 });

	sandbag.setup({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });

	// Side Attacks
	sideAttackLeft.setup(true);
	sideAttackRight.setup(false);
}

void Game::endLag()
{
	if (endLagTimer < endLagDuration)
	{
		endLagTimer++;
	}
	else if (endLagTimer >= endLagDuration)
	{
		// Reset timer
		endLagTimer = 0;

		// Can attack becomes true
		canAttack = true;
	}
}

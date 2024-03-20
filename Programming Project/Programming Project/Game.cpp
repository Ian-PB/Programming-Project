/// <summary>
/// @author Ian Perez Bunuel
/// @date March 2024
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

	srand(time(nullptr));
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

		// Mouse
		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			processMouseDown(newEvent);
		}

		if (sf::Event::MouseMoved == newEvent.type)
		{
			processMouseMove(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

void Game::processMouseDown(sf::Event t_event)
{
}

void Game::processMouseMove(sf::Event t_event)
{
	// Gets the position of the mouse
	mousePos.x = static_cast<float>(t_event.mouseMove.x);
	mousePos.y = static_cast<float>(t_event.mouseMove.y);
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

	player.checkDirection();
	player.rotateToMouse(mousePos);

	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		enemies[i].moveToTarget({ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f });
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);

	// Player
	m_window.draw(player.getBody());
	// Enemies
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		m_window.draw(enemies[i].getBody());
	}

	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupObjects()
{
	player.setup({200, 200});

	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		enemies[i].setup({ static_cast<float>(rand() % SCREEN_WIDTH), static_cast<float>(rand() % SCREEN_HEIGHT) });
	}
}

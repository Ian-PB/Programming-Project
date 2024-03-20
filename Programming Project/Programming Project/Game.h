/// <summary>
/// author Ian Perez Bunuel March 2024
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Constants.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processMouseDown(sf::Event t_event);
	void processMouseMove(sf::Event t_event);

	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupObjects();


	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game


	// Objects
	Player player;
	Enemy enemies[MAX_ENEMIES];

	// Mouse stats
	sf::Vector2f mousePos;
};

#endif // !GAME_HPP


/// <summary>
/// author Pete Lowe May 2019
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
#include "Globals.h"
#include "Player.h"
#include "Sandbag.h"
#include "Platform.h"
// Including attacks
#include "DownAttack.h"
#include "NeutralAttack.h"
#include "SideAttack.h"
#include "UpAttack.h"

// Controller
#include "Controller.h"

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
	void processController();
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupObjects();

	sf::RenderWindow m_window; // main SFML window

	// Objects
	Player player;
	Sandbag sandbag;
	Platform platforms[3];
	// Attacks
	DownAttack downAttack;
	UpAttack upAttack;
	SideAttack sideAttackLeft;
	SideAttack sideAttackRight;
	NeutralAttack neutralAttack;

	void endLag();
	bool canAttack = true;
	bool damageDone = false;
	int endLagTimer = 0;
	int endLagDuration; // Set after doing an attack

	// Controller
	Controller controller;
	bool controllerConnected = false;
	bool buttonPressed = false;


	// Sandbag Knockback info
	float knockbackAngle = 0.0f;
	float knockbackPower = 0.0f;
	int damageTaken = 0;

	// Sandbag Percentage
	sf::Font font;
	sf::Text sandbagPercentage;

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP


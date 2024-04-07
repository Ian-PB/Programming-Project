#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include <iostream>


struct ControllerState
{
	bool A;                          // 0
	bool B;                          // 1
	bool X;                          // 2 
	bool Y;                          // 3
	bool LB;                         // 4
	bool RB;                         // 5
	bool LeftThumbStickClick;        // 8
	bool RightThumbStickClick;       // 9
	bool DpadUp;
	bool DpadDown;
	bool DpadLeft;
	bool DpadRight;
	bool Start;                      // 6
	bool Back;                       // 7
	bool Xbox; // Xbox button        // 10

	float RTrigger; // How much the Right trigger is pressed
	float LTrigger; // How much the Left trigger is pressed
	sf::Vector2f RightThumbStick; // The direction the Right thumb stick is in
	sf::Vector2f LeftThumbStick; // The direction the Left thumb stick is in
};

class Controller
{
private:

	const int DPAD_THRESHOLD = 50;

public:
	// The current state of the controller
	ControllerState currentState;
	// The state of the controller before the current state. Used to check what was pressed
	ControllerState previousState;

	// Update for the controller
	void Controller::update();

	bool connectCheck();
};


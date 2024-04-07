#include "Controller.h"

void Controller::update()
{
	// Set the previous state before checking for button presses
	previousState = currentState;

	//// Check for button presses ////

	// These give back a bool depending if they're pressed or not
	currentState.A = sf::Joystick::isButtonPressed(0, 0);
	currentState.B = sf::Joystick::isButtonPressed(0, 1);
	currentState.X = sf::Joystick::isButtonPressed(0, 2);
	currentState.Y = sf::Joystick::isButtonPressed(0, 3);
	currentState.LB = sf::Joystick::isButtonPressed(0, 4);
	currentState.RB = sf::Joystick::isButtonPressed(0, 5);
	currentState.Back = sf::Joystick::isButtonPressed(0, 6);
	currentState.Start = sf::Joystick::isButtonPressed(0, 7);
	currentState.LeftThumbStickClick = sf::Joystick::isButtonPressed(0, 8);
	currentState.RightThumbStickClick = sf::Joystick::isButtonPressed(0, 9);
	currentState.Xbox = sf::Joystick::isButtonPressed(0, 10);

	// if the statement before ? is true, then do the thing before : else do the other
	currentState.DpadRight = (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) > DPAD_THRESHOLD) ? true : false;
	currentState.DpadLeft = (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) > -DPAD_THRESHOLD) ? true : false;
	currentState.DpadUp = (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) > DPAD_THRESHOLD) ? true : false;
	currentState.DpadDown = (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) > -DPAD_THRESHOLD) ? true : false;

	// Gets how far they are pressed
	currentState.LTrigger = sf::Joystick::getAxisPosition(0, sf::Joystick::Z);
	currentState.RTrigger = -sf::Joystick::getAxisPosition(0, sf::Joystick::Z);

	currentState.LeftThumbStick = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Y));
	// U and R is the equivalent of X and Y axis
	currentState.RightThumbStick = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::U), sf::Joystick::getAxisPosition(0, sf::Joystick::R));

}

bool Controller::connectCheck()
{
	// Check for the start button is pressed
	currentState.Start = sf::Joystick::isButtonPressed(0, 7);

	// If it was pressed
	if (currentState.Start)
	{
		return true;
	}
	// If not pressed
	else
	{
		return false;
	}
}

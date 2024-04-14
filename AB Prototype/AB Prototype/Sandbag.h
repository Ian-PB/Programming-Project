#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Platform.h"
#include <iostream>

class Sandbag
{
public:
    Sandbag();
    void setup(sf::Vector2f t_pos);

    // "Get" Functions
    sf::RectangleShape getBody() { return body; }
    sf::RectangleShape getChecker() { return groundChecker; }

    sf::CircleShape getIndicatorBody() { return indicator; }

    void groundCheck(Platform t_platform);

    void gravity();
    void checkBoundries();

    // Knockback
    void knockback(int t_angleD, float& t_power, int t_damage);
    int bounce(float t_angleD);

    // Damage
    void takeDamage(int t_damage);

    // Indicator that shows where the sandbag is while off screen
    void offScreenIndicator();

    bool hitAgain = false;
    bool knockingBack = false;

    // Off screen Indicator
    bool indicatorActive = false;

    // Damage done to sandbag
    int percentage = 0;

    bool onGround = false;

private:

    sf::Texture sandbagTexture;
    sf::Sprite sprite;
    sf::RectangleShape body;
    float height = 100;
    float width = 50;

    sf::Vector2f position;

    // Knockback
    float deceleration = 0;
    const float POWER_GRAVITY_MULTIPLIER = 1.5f;
    const float PERCENTAGE_DIVIDER = 10.0f;

    sf::Vector2f direction;

    // Off screen Indicator
    sf::CircleShape indicator;
    float indicatorRadius = 20;
    sf::Vector2f indicatorPos = { 0.0f, 25.0f };

    // Ground checking
    sf::RectangleShape groundChecker;
    const sf::Vector2f GROUND_CHECK_DISPLACEMENT = { 0.0f, (height / 2.0f) };
    bool hitGround = false;


};

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Healthbar {
public:
    Healthbar();
    int getHealth();
    void setHealth(int a);          // Sets health and calls update
    void draw(sf::RenderTarget& target) const;
    void setPosition(float x, float y);     // the two components of the health bar must be moved together

//private:
    int health;                     // Value of Pokemon's health is stored here
    sf::RectangleShape outline;     // Basic outline of healthbar
    sf::RectangleShape bar;         // Bar that will change length and color
    sf::Sprite heart;               // Little heart for next to the healthbar
    sf::Texture heart_pic;             
    void update();                  // When health changes, this function is called to update the bar visually
};
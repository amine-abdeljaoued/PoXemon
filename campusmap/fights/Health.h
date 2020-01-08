#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Healthbar {
public:
    Healthbar();
    int getHealth();
    void setHealth(int a);          // Sets health and calls update
	void decrease(int i);
    void draw(sf::RenderWindow& target) const;
    void draw(sf::RenderTexture& texture) const;
    void setPosition(float x, float y);     // the three components of the health bar must be moved together
    void update();                  // When health changes, this function is called to update the bar visually

    // The following two parameters won't ever change when we decide what they are
    // Just need them here so that if we want to change sizes its not a mess
    int healthwidth;          // width of the bar that shows our pokemon's health
    int healthheight;

    int health;                     // Value of Pokemon's health is stored here

    // Visuals
    sf::RectangleShape outline;     // Basic outline of healthbar
    sf::RectangleShape healthbar;   // Bar that will change length and color
    sf::Sprite heart;               // Little heart for next to the healthbar
    sf::Texture heart_pic;  
    sf::Sprite bar;          
    sf::Texture bar_pic;

    // Text
    int level;
    std::string name;
    sf::Font font;
	sf::Text name_text;
    sf::Text level_text;
};
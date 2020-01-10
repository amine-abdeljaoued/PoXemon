#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

//might be better to put that inside the backpack class ??
class Pokemon_Button
{
public:

	Pokemon_Button() {};
	Pokemon_Button(std::string& name, int& lvl, int& health, int&i );
	void setHealth(int& a);
	void Levelup();
	void draw(sf::RenderWindow& target);
	void setPosition(float x, float y);     // all the components of the health bar must be moved together
	void update_mouse(sf::Vector2f& mouse_pos, int&clicked_button); //check for clicked buttons    
	void update();

	int index;

	// The following two parameters won't ever change when we decide what they are
	// Just need them here so that if we want to change sizes its not a mess
	int healthwidth;          // width of the bar that shows our pokemon's health
	int healthheight;

	int health;// Value of Pokemon's health is stored here

	// Visuals
	sf::Texture pokemon_pic;
	sf::Sprite sprite;
	sf::RectangleShape outline;     // Basic outline of healthbar
	sf::RectangleShape healthbar;   // Bar that will change length and color
	sf::Sprite heart;               // Little heart for next to the healthbar
	sf::Texture heart_pic;
	sf::Sprite bar;
	sf::Texture bar_pic;
	sf::CircleShape red_circle;

	//Text
	int level;
	std::string name;//need it ?
	sf::Font font;
	sf::Text name_text;
	sf::Text level_text;


};


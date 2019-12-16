#pragma once
#include "Bullet.h"
#include "Bullet_bar.h"
#include <SFML/Graphics.hpp>
#include "Collision.h"

// This is the class that stores how many bullets we have/can shoot/are shooting 
// It also controls the movement of all of the bullets being shot

class Artillery{
public:
    Artillery();
    bool was_released; // this is used to shoot only one bullet per click
    void draw(sf::RenderTarget& target) const;
    // new_shot is for the player
    void new_shot(float& x, float& y, const sf::FloatRect& bounds, sf::RenderTarget& window, const sf::Vector2i& mouse);
    // new_shot_opp is for the opponent
    void new_shot_opp(float& x, float& y, const sf::FloatRect& bounds, sf::RenderTarget& window, float& xshoot, float& yshoot);
    int update(float& deltaTime, sf::Clock& clock, sf::Time& elapsed, const sf::Sprite & opponent_sprite, float& groundY);


//private:
	std::vector<Bullet> bullets;    // Bullets we use can depend on Pokemon
                                    // If so, bullet needs to have constructors which are passed through artillery
	
	int max_available_bullets;
	int available_bullets;
	BulletBar bulletbar;

};
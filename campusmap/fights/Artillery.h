#pragma once
#include "Bullet.h"
#include "Bullet_bar.h"
#include <SFML/Graphics.hpp>
#include "Collision.h"
#include "Special_Attacks_bar.h"

// This is the class that stores how many bullets we have/can shoot/are shooting 
// It also controls the movement of all of the bullets being shot

class Artillery{
public:
    Artillery();
    ~Artillery();
    bool was_released; // this is used to shoot only one bullet per click
    void draw(sf::RenderWindow& target) ;
    void draw(sf::RenderTexture& texture) ;
    // new_shot is for the player
    void new_click(float& x, float& y, const sf::FloatRect& bounds, sf::RenderWindow& window, const sf::Vector2i& mouse);
    void new_shot(float& x, float& y, const sf::FloatRect& bounds, sf::RenderWindow& window, const sf::Vector2i& mouse);
    void new_shot_special_attack1(float& x, float& y, const sf::FloatRect& bounds, sf::RenderWindow& window, const sf::Vector2i& mouse);
    // new_shot_opp is for the opponent
    void new_shot_opp(float& x, float& y, const sf::FloatRect& bounds, sf::RenderWindow& window, float& xshoot, float& yshoot);
    int update(sf::RenderWindow& window, float& deltaTime, sf::Clock& clock, sf::Time& elapsed, sf::Clock& clock1, sf::Clock& clock2, sf::Clock& clock3, 
                const sf::Sprite & opponent_sprite, float& groundY);
    void initialise();

	std::vector<Bullet*> bullets;
    int attack_type = 0; 
    // Attack type:
    // 0: standard
    // 1-3: special attack 1-3

	int type; // same type as its pokemon
	int max_available_bullets;
	int available_bullets;
	BulletBar bulletbar;
    Special_Attacks_Bar attacksbar;
};
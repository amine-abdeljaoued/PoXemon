#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


//remarks / stuff to change
/*
We sould be able to throw a pokeball only if we have some in our backpack
We can only throw one pokeball at a time
When we throw one, the game should 'stop', until we know whether or not we caatch the opponent
Normally, the pokeball is not thrown by the pokemon but by the player
*/

class Pokeball {
public:
    float velocityX ;  //Set the speed of each of the pokeballs
    float ballHeight = 300;
    float velocityY;
    float x;
    float y;
    
    sf::Sprite ball;
    
    float gravity = 981.0f ;//This will make the parabolic trajectory
    float airfriction = 0.4;
    float coefimpact = 0.2;
    bool in_air;
    int bounce;
    
    
    
    
    //void Pokeball_shoot(float& deltaTime, sf::RenderWindow& window);
    
    void dissapear();
    
    void setPosition(float& xpos, float& ypos);
    bool update(float deltaTime,sf::RenderWindow& window,float proba, sf::Clock &clock2, sf::Time &elapsed2);
    bool catched(float proba, sf::Clock& clock, sf::Time& elapsed);
    bool waiting = false;
    
    Pokeball();
private:
    sf::Texture pic;
};

class Normalball: public Pokeball{
public:
    float proba;
	float proba_max;
    Normalball();
private:
    sf::Texture pic1;
};

class Superball: public Pokeball{
public:
    float proba;
	float proba_max;
    Superball();
private:
    sf::Texture pic2;
};

class Masterball: public Pokeball{
public:
    float proba;
	float proba_max;
    Masterball();
private:
    sf::Texture pic3;
};


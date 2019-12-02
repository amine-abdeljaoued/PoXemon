#include <iostream>
#include "Pokemon.h"
#pragma once



class Opponent: public Pokemon{

protected:
    Pokemon player;
public:
	//This sould go in the cpp
    Opponent(Pokemon player_poke,float xstart, float ystart, float h, float v, float hp, std::string path, float pokemon_rarity)
    :Pokemon(xstart, ystart, h, v, hp, path,pokemon_rarity){
        player=player_poke;
		speed = 400;
		int randomDirection[2] = { -1,1 };
		int randomIndex = rand() % 2;
		direction = randomDirection[randomIndex];
		time_change_dir = 0.3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 - 0.3))); //random float between 0.3 and 2
    };

    //void updateMovement(float& deltaTime);
    void update(float& deltaTime, sf::RenderTarget& target);
    void move(float& deltaTime);

	int direction;
	float time_change_dir; //time before changing direction (updated each time the bot changes direction)
	sf::Clock clock;
	sf::Time elapsed_direction;
	
};
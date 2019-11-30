#include <iostream>
#include "Pokemon.h"
#pragma once



class Opponent: public Pokemon{

protected:
    Pokemon player;
public:
    Opponent(Pokemon player_poke,float xstart, float ystart, float h, float v, float hp, std::string path, float pokemon_rarity)
    :Pokemon(xstart, ystart, h, v, hp, path,pokemon_rarity){
        player=player_poke;
    };
    //void updateMovement(float& deltaTime);
    void update(float& deltaTime);
    void move(float& deltaTime);
};
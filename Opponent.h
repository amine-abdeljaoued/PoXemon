#include <iostream>
#include "Pokemon.h"



class Opponent: public Pokemon{

protected:
    Pokemon player;
public:
    Opponent(float xstart, float ystart, float h, float v):Pokemon(xstart, ystart,h, v){};
    //void updateMovement(float& deltaTime);
    void update(float& deltaTime);
    void move(float& deltaTime);
};
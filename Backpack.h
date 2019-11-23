#pragma once
#include "Pokemon.h"
#include "Pokeball.h"

//We carry this backpack throughout the game
//->we need to talk with the other teams for that

class Backpack
{
    public:
        Pokeball new_Pokeball;
        std::map<std::string, int> dict_pokeball;
    
        void Pokeball_shoot(float& deltaTime, sf::RenderWindow& window);
        
        void draw (sf::RenderTarget &target) const;
        
        Backpack();
    
        
        //void update();
        //We can have up to 6 pokemons in our backpack
        //we can have up to 3 pokeballs

        //It should have several methods
        // for example : replace pokemons, heal them ...

};


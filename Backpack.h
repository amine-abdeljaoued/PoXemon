#pragma once
#include "Pokemon.h"
#include "Pokeball.h"

//We carry this backpack throughout the game
//->we need to talk with the other teams for that

class Backpack
{
    public:
        Normalball new_Normalball;
        Superball new_Superball;
        Masterball new_Masterball;
    
        std::map<std::string, int> dict_pokeball;
        sf::RectangleShape clickbox;
        sf::Sprite normalball;
        sf::Sprite superball;
        sf::Sprite masterball;
    
        void Pokeball_shoot(float& deltaTime, sf::RenderWindow& window);
        
        void Pokeball_throw(Pokeball Poke,float& deltaTime, sf::RenderWindow& window);
        
        void draw (sf::RenderTarget &target) const;
        
        bool masternow;
        bool supernow;
        bool normalnow;
        
        
        
        Backpack();
    
        
        //void update();
        //We can have up to 6 pokemons in our backpack
        //we can have up to 3 pokeballs

        //It should have several methods
        // for example : replace pokemons, heal them ...
    private:
    sf::Texture normaltext1;
    sf::Texture normaltext2;
    sf::Texture normaltext3;
};


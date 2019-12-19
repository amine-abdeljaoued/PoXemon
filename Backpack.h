#pragma once
#include "Opponent.h"
#include "Pokeball.h"
#include "Pokemon_Button.h"
#include "Backpack_Pokemon.cpp"


//We carry this backpack throughout the game
//->we need to talk with the other teams for that

class Backpack
{
    public:
		Backpack();

        // Our Pokeballs
        Normalball new_Normalball;
        Superball new_Superball;
        Masterball new_Masterball;

        bool masternow;
        bool supernow;
        bool normalnow;

        // Our Pokemons
        Backpack_Pokemon* backpack_pokemons[3]; //maybe more ?

        // Visuals for the fight
        std::map<std::string, int> dict_pokeball;
        sf::RectangleShape clickbox;
        sf::Sprite normalball;
        sf::Sprite superball;
        sf::Sprite masterball;
    
        // Functions
        void Pokeball_shoot(float& deltaTime, sf::RenderWindow& window, sf::Clock &clock2, sf::Time & elapsed2);
        void Pokeball_throw(Pokeball Poke,float& deltaTime, sf::RenderWindow& window);
        void draw (sf::RenderWindow &target) const;

        // Opponent
		Opponent* opponent;
		void set_opponent(Opponent* opponent);
        
        // Functions for our pokemons
		bool alive_pokemons();//false iff all pokemons are dead
        void change_pokemons();
        void heal_pokemons() {//should be called every time we enter the shop
			for (unsigned int i = 0; i < 3; i++) {
				(*backpack_pokemons[i]).health = 100;
			}
		}


    private:
    sf::Texture normaltext1;
    sf::Texture normaltext2;
    sf::Texture normaltext3;
};


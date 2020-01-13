#pragma once
#include "Opponent.h"
#include "Pokeball.h"
#include "Pokemon_Button.h"

class ReturnValue{
    public:
    int i;
    std::string string;
};

class Backpack
{
    public:
		Backpack();
        ~Backpack();
        void setBackpack(int i);
        // Our Pokeballs
        Normalball new_Normalball;
        Superball new_Superball;
        Masterball new_Masterball;

        bool masternow;
        bool supernow;
        bool normalnow;

        ReturnValue value;

        // Our Pokemons
        Backpack_Pokemon* backpack_pokemons[3]; 

        // Visuals for the fight
        std::map<std::string, int> dict_pokeball;
        sf::RectangleShape clickbox;
        sf::Sprite normalball;
        sf::Sprite superball;
        sf::Sprite masterball;
    
        // Functions
        ReturnValue Pokeball_shoot(float& deltaTime, sf::RenderWindow& window, sf::Clock &clock2, sf::Time & elapsed2);// was void
        void Pokeball_throw(Pokeball Poke,float& deltaTime, sf::RenderWindow& window);
        void draw (sf::RenderWindow &target) const;
        void draw (sf::RenderTexture& texture) const;
        void reset();

        // Opponent
		Opponent* opponent;
		void set_opponent(Opponent* opponent);
        
        // Functions for our pokemons
		bool alive_pokemons();//false iff all pokemons are dead
        void change_pokemons();
        void heal_pokemons() {//should be called every time we enter the shop
			for (unsigned int i = 0; i < 3; i++) {
				if (backpack_pokemons[i]) {
					(*backpack_pokemons[i]).health = 100;
				}
			}
		}

        int bag_number;

    private:
    sf::Texture normaltext1;
    sf::Texture normaltext2;
    sf::Texture normaltext3;
};


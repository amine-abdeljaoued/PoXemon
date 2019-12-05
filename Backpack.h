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
    
        void Pokeball_shoot(float& deltaTime, sf::RenderWindow& window, sf::Clock &clock2, sf::Time & elapsed2);
        
        void Pokeball_throw(Pokeball Poke,float& deltaTime, sf::RenderWindow& window);
        
        void draw (sf::RenderTarget &target) const;
        
        bool masternow;
        bool supernow;
        bool normalnow;

		class Backpack_Pokemon{

		public:
			Backpack_Pokemon(std::string& n, int& i, int& h) {
				name = n;
				index = i;
				health = h;
			}

			std::string name;
			int index;//to find it easily
			int health;
		};

		Backpack_Pokemon* backpack_pokemons[3];

        Backpack();
    
		void change_pokemons() {//to be completed
		}

		void heal_pokemons() {//should be called every time we enter the shop
			for (unsigned int i = 0; i < 3; i = i + 1) {
				(*backpack_pokemons[i]).health = 100;
			}
		}



    private:
    sf::Texture normaltext1;
    sf::Texture normaltext2;
    sf::Texture normaltext3;
};


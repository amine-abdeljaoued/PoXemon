#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Pokeball.h"
#include "Backpack.h"
#include "Player.h"
#include "Opponent.h"
#include "Pokemon_Button.h"
#include "StateFunctions.h"
#include "../pokemons_structure.hpp"
#include "../Backpack_map.hpp"

class Fight 
{
public:
    // basic constructor
    Fight();
    ~Fight();
    Fight(sf::RenderWindow& window); 

    // start a specific fight
    void initialise_wild (BackpackMap& pbag_map, sf::RenderWindow& window); // initialise a fight with a wild pokemon
    void initialise_trainer (BackpackMap& pbag_map, Backpack& popponent_bag, sf::RenderWindow& window); // initilaise a fight with a trainer
    void initialise_basic(BackpackMap& pbag_map, sf::RenderWindow& window);
    Opponent* get_wild_pokemon(sf::RenderWindow& window, int type);

    Backpack bag;
    Backpack opponent_bag;
    BackpackMap bag_map;

    // Boundaries
	float groundY; //Cannot go below this height
    
    //Parameters of the game
    int state = 1;  // 0 = return to map
                    // 1 = start menu
                    // 2 = normal fight mode
                    // 3 = pokeball landed in centre -- to be implemented
                    // 4 = caught the pokemon
                    // 5 = we died -> choose another or quit
                    // 6 = opponent died and trainer still has pokemons
                    // 7 = end of the duel against a trainer
                    // 8 = end of the fight against a wild pokemon
                    // 9 = pokeball is in air (transition state before knowing if we caught the pokemon)
                    // 10 = countdown
                    // 11 = we caught the pokemon with the pokeball
                    // 12 = the pokeball didn't work
                    // 15 = how to play
                    // 20 = all pokemons dead -> go to health shop

    char game_mode; // 'w' : wild pokemon
                    // 't' : trainer
    Pokemon_Button* poke_buttons[3]; // our three pokemons
    Player* pplayer;
    Opponent* popponent;
    StateFunctions1 functions1;
    StateFunctions56 functions56;

    // Updating the window
    int update(sf::RenderWindow& window);

    // Used for blurring
    sf::Shader shader;

    // Visuals for always
    sf::Font font;
    sf::Texture BackgroundTexture;
	sf::Sprite background;

    // States 2,5,6
    float deltaTime;
    sf::Clock clock;
    sf::Clock clock_regenerate_bullets;	
    sf::Time elapsed;
    sf::Clock clock2;
    sf::Time elapsed2;

	//leave button (when the game is finished)
	sf::Text leave;
	sf::Texture arrow;
	sf::Sprite arrow_sprite;
	
    // For the player
	sf::Clock attack_1_clock;
	sf::Clock attack_2_clock;
	sf::Clock attack_3_clock;
	sf::Time attack_1_time;
	sf::Time attack_2_time;
	sf::Time attack_3_time;
	
    // For the opponent
	sf::Clock attack_1_clock_opp;
	sf::Clock attack_2_clock_opp;
	sf::Clock attack_3_clock_opp;
	sf::Time attack_1_time_opp;
	sf::Time attack_2_time_opp;
	sf::Time attack_3_time_opp;
    
	int counter; // do we need these?
	int i = 0;

    // States 5,6
    sf::Text text_fainted;// "pokemon name" fainted !
	sf::Text leave_fight;
	sf::Text choose_pokemon;
	sf::Texture running;
	sf::Sprite running_sprite;
    int clicked_button; 

    // state 7
	sf::Text wonlost;
	bool won;

	//pokeball states
	sf::Text caught;

    //will be useful
	sf::Text money;
	sf::Text xp;
};
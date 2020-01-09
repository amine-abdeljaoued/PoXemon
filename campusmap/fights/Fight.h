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

// test

class Fight 
{
public:
    // basic constructor
    Fight();
    Fight(sf::RenderWindow& window); 

    // start a specific fight
    void initialise (char& mode, Backpack& pbag, Backpack& popponent_bag, Player* player, Opponent* opponent, sf::RenderWindow& window); // any - to be deleted
    void initialise_wild (Backpack& pbag, Player* player, Opponent* opponent, sf::RenderWindow& window); // initialise a fight with a wild pokemon
    void initialise_trainer (Backpack& pbag, Backpack& popponent_bag, Player* player, sf::RenderWindow& window); // initilaise a fight with a trainer

    Backpack bag;
    Backpack opponent_bag;
    // Boundaries
	float groundY = 300.0f; //Cannot go below this height - NB INITIALISE WITH WINDOW??
    float groundX = 1000.f;
    
    //Parameters of the game
    int state = 1;  // 0 = return to map
                    // 1 = start menu
                    // 2 = normal fight mode
                    // 3 = pokeball landed in centre -- to be implemented
                    // 4 = caught the pokemon
                    // 5 = we died -> choose another or quit
                    // 6 = opponent died
                    // 7 = no more pokemons -> go to hospital/shop
                    // 8 = how to play menu
                    // 9 = clicked start -> choose pokemon to play with
                    // 10 = countdown
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

    //will be useful
	sf::Text money;
	sf::Text xp;
};
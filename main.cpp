#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Pokemon.h"
#include "Pokeball.h"
#include "Bullet.h"
#include "Artillery.h"
#include "Backpack.h"
#include "Backpack_Pokemon.cpp"
#include "Player.h"
#include "functions_state1.cpp"
#include "functions_state_5_6.cpp"
#include "Opponent.h"
#include "Pokemon_Button.h"

float groundY = 300.0f; //Cannot go below this height
float groundX = 1000.f;

// We declare a variable "state" for fights which shows the game state
// 1 = start menu
// 2 = normal fight mode
// 3 = pokeball landed in centre -- to be implemented
// 4 = caught the pokemon
// 5 = we died -> choose another or quit
// 6 = opponent died
// 7 = no more pokemons -> go to hospital/shop
// 8

int main ()
{	
	//we need that stuff now but it will actually be initialized earlier in the game

	//----------------------------------------------------------------------------
	//char game_mode = 'w'; //we play against a wild pokemon
	char game_mode = 't'; //we play against a trainer

	Backpack bag;
	std::string name1 = "jistolwer";
	std::string name2 = "auron";
	std::string name3 = "husabus";
	Backpack_Pokemon poke1(name1, 1, 0, 50, 20);//not the actual types though
	Backpack_Pokemon poke2(name2, 1, 1, 60, 20);
	Backpack_Pokemon poke3(name3, 1, 2, 70, 30);
	bag.backpack_pokemons[0] = &poke1;
	bag.backpack_pokemons[1] = &poke2;
	bag.backpack_pokemons[2] = &poke3;
	Pokemon_Button* poke_buttons[3] = { &poke1.button, &poke2.button, &poke3.button };//not here !!!
	//should be in the backpack maybe

	Backpack opponent_bag;
	name1 = "donryle";
	name2 = "fepeur";
	name3 = "geodos";
	Backpack_Pokemon opoke1(name1, 1, 0, 50, 10);
	Backpack_Pokemon opoke2(name2, 1, 1, 60, 20);
	Backpack_Pokemon opoke3(name3, 1, 2, 70, 30);
	opponent_bag.backpack_pokemons[0] = &opoke1;
	opponent_bag.backpack_pokemons[1] = &opoke2;
	opponent_bag.backpack_pokemons[2] = &opoke3;

	//--------------------------------------------------------------------

	// Stuff used everywhere
	sf::Font font;
	if (!font.loadFromFile("upheavtt.ttf")) { std::cout << "could not load font" << std::endl; }
	else {font.loadFromFile("upheavtt.ttf");}

	Player* pplayer = new Player(10.f, groundY, 200.f, 500.f, poke1);//by default, we take the first pokemon of the backpack
	//do we want to be able to choose our pokemon at the beginning of the fight ?
	Opponent* popponent = new Opponent(1000.f,groundY,200.f, 800.f, opoke1);
	bag.set_opponent(popponent);
	(*pplayer).set_enemy(popponent);
	(*popponent).set_enemy(pplayer);
	int state = 1;

    sf::RenderWindow window(sf::VideoMode(1400, 700), "My window");

	sf::Texture BackgroundTexture;
	sf::Sprite background;
	initialise_background(window, "Images/grassbg.png", background, BackgroundTexture);

	// Objects that we need for state 1:
	// Two buttons: to start or to find out how to play
	sf::RectangleShape start_button;
	sf::RectangleShape info_button;
	sf::Text start_text;
	sf::Text info_text;
	sf::Text intro_text;
	intro_text.setString("You are about to fight " + (*popponent).name);
	sf::Sprite opp = (*popponent).sprite;
	sf::Sprite star;
	sf::Texture star_texture;
	initialise_buttons(start_button, info_button, window, font, start_text, info_text, intro_text, opp, star, star_texture);

	// Objects for state 2: (also used for states 5 and 6)
	float deltaTime = 0.0f;

    sf::Clock clock;
    sf::Clock clock_regenerate_bullets;
    sf::Time elapsed;
    
    sf::Clock clock2;
    sf::Time elapsed2;
    
	static int counter=0;
	int i = 0;


	//Objects needed for states 5, 6 :-------------------------

	sf::Text text_fainted;// "pokemon name" fainted !
	sf::Text leave_fight;
	sf::Text choose_pokemon;
	leave_fight.setString("Run");
	choose_pokemon.setString("Choose your next pokemon");

	sf::Texture running;
	sf::Sprite running_sprite;

	if (!running.loadFromFile("Images/running_trainer.png"))std::cout << "could open running trainer" << std::endl;
	running.loadFromFile("Images/running_trainer.png");
	running_sprite.setTexture(running);
	running_sprite.setScale(2, 2);
	running_sprite.setOrigin(running_sprite.getLocalBounds().width / 2, running_sprite.getLocalBounds().height / 2);
    running_sprite.setPosition(window.getSize().x *2/ 3, window.getSize().y / 2);

	int clicked_button = -2; //no clicked button for the moment

	//Objects for state 7:
	sf::Text wonlost;
	bool won;

	//will be useful
	sf::Text money;
	sf::Text xp;



	// run the program as long as the window is open
	while (window.isOpen())
	{
		
		deltaTime = clock.restart().asSeconds();
		elapsed = clock_regenerate_bullets.getElapsedTime();
        elapsed2 = clock2.getElapsedTime();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				std::cout << "Goodbye" << std::endl;
				window.close();
			}
		}

		if (state==1){
			// Initial game menu - functions used here are in "functions.cpp"
			i++;
			//std::cout<<i<<std::endl;
			state = update_state1(window, start_button, info_button, star);
			window.clear(sf::Color::Blue);
			window.draw(background);
			draw1(window, start_button, info_button, start_text, info_text, intro_text, opp, star);
			
			//in this state, we should be able to choose our pokemon
			//we will use pokemon buttons
		}

		else if (state==2){ //fight
			
			//std::cout << (*popponent).health.health << std::endl;
			(*pplayer).update(deltaTime, window, clock_regenerate_bullets, elapsed, groundY);
			(*popponent).update(deltaTime, window, clock_regenerate_bullets, elapsed, groundY);

			//player dies
			if ((*pplayer).health.health <= 0) {
				bag.backpack_pokemons[(*pplayer).index]->health = 0; //set health of the corresponding backpack pokemon to 0

				if (!bag.alive_pokemons()) { // no more alive pokemons

					if (game_mode == 't') { //lost the duel
						initialize_state7(false, wonlost, font, window);
						won = false;
						state = 7;
					}
					else {//lost against a wild pokemon
						initialize_state_8((*pplayer), font, text_fainted, window);
						won = false;
						state = 8;
					}
				}

				else {
					initialize_state_5_6(game_mode, (*pplayer), font, text_fainted, choose_pokemon, leave_fight, window, poke_buttons, running_sprite);
					state = 5;
				}
			}

			//opponent dies
			if ((*popponent).health.health <= 0) {
				opponent_bag.backpack_pokemons[(*popponent).index]->health = 0;
				bag.backpack_pokemons[(*pplayer).index]->health = (*pplayer).health.health;//update health of our pokemon in the backpack

				if (game_mode == 't') { //if we are playing against a trainer

					if (! opponent_bag.alive_pokemons()) { //all of the trainer's pokemons are dead -> we won the duel
						std::cout << "you won !!!" << std::endl;
						initialize_state7(true, wonlost, font, window);
						won = true;
						state = 7;
					}

					else { //the trainer still has pokemons -> he takes the next one
						initialize_state_5_6(game_mode, (*pplayer), font, text_fainted, choose_pokemon, leave_fight, window, poke_buttons, running_sprite);
						//initialize_next_opp(); // create a text + image : you are about to fight 'next opponent'
						state = 6;
					}

				}
				else // (game_mode == 'w')
				{
					won = true;
					initialize_state_8((*popponent), font, text_fainted, window);
					state = 8;

					//text element : 'opponent fainted'
					//text element : you won the fight against
					//gained xp...
					//go back to map
				}

			}

			bag.Pokeball_shoot(deltaTime, window, clock2, elapsed2);
			window.clear(sf::Color::Blue);
			window.draw(background);
			bag.draw(window);
			(*pplayer).draw(window);
			(*popponent).draw(window);
		}

		else if (state == 5) {//player dies

			(*pplayer).death_disappear(deltaTime);
			//make gravity work 
			fall((*pplayer), groundY, deltaTime);
			fall((*popponent), groundY, deltaTime);

			//bullets that were shot before the end continue their movement
			(*pplayer).bullets.update(window, deltaTime, clock, elapsed, (*popponent).sprite, groundY);
			(*popponent).bullets.update(window, deltaTime, clock, elapsed, (*popponent).sprite, groundY);

			//draw stuff
			window.clear(sf::Color::Blue);
			window.draw(background);
			(*pplayer).draw(window);
			(*popponent).draw(window);

			//draw the menu
			//maybe we should wait a few seconds before drawing this
			update_state_5_6(game_mode, window, poke_buttons, clicked_button, running_sprite);//check for clicked buttons
			draw_state_5_6(game_mode, font, text_fainted, choose_pokemon, leave_fight, window, poke_buttons, running_sprite);

			if (clicked_button >= 0) {//we clicked on a pokemon button
				delete pplayer;
				Player* pplayer = new Player(10.f, groundY, 200.f, 500.f, *(bag.backpack_pokemons[clicked_button]));//reinitialize player with the chosen pokemon
				(*popponent).x = 1000.f;//reset opponent's position
				bag.set_opponent(popponent);
				//dont forget to reset enemies
				(*pplayer).set_enemy(popponent);
				(*popponent).set_enemy(pplayer);

				state = 2;//go back to fight
				clicked_button = -2;//set it unclicked
			}

			if (clicked_button == -1) {//we clicked on the run button
				delete pplayer;
				delete popponent;
				//black screen
				//go back to where we were on the map
			}
		}

		else if (state == 6) { //(game mode 'w') opponent dies and trainer still has pokemons

			(*popponent).death_disappear(deltaTime);
			fall((*pplayer), groundY, deltaTime);
			fall((*popponent), groundY, deltaTime);
			(*pplayer).bullets.update(window, deltaTime, clock, elapsed, (*popponent).sprite, groundY);
			(*popponent).bullets.update(window, deltaTime, clock, elapsed, (*popponent).sprite, groundY);

			window.clear(sf::Color::Blue);
			window.draw(background);
			(*pplayer).draw(window);
			(*popponent).draw(window);

			int index = (*popponent).index;
			//you are about to fight + 'opponent'
			//have an image, text etc...

			
			update_state_5_6(game_mode, window, poke_buttons, clicked_button, running_sprite);//check for clicked buttons
			draw_state_5_6(game_mode, font, text_fainted, choose_pokemon, leave_fight, window, poke_buttons, running_sprite);

			if (clicked_button >= 0) {//we clicked on a pokemon button
				delete pplayer;//maybe it would be better not to delete it if we chose the same ?
				Player* pplayer = new Player(10.f, groundY, 200.f, 500.f, *(bag.backpack_pokemons[clicked_button]));//reinitialize player with the chosen pokemon
				
				delete popponent;
				Opponent* popponent = new Opponent(1000.f, groundY, 200.f, 500.f, *(opponent_bag.backpack_pokemons[index+1]));//reinitialize opponent with the next one in the trainer's bag //change it randomly ?

				bag.set_opponent(popponent);
				//dont forget to reset enemies
				(*pplayer).set_enemy(popponent);
				(*popponent).set_enemy(pplayer);

				state = 2;//go back to fight
				clicked_button = -2;//set it unclicked
			}

		}

		else if (state == 7) { //end of the duel against a trainer

		// won == true: no more alive opponent pokemons -> we won the duel
		// won == false: no more alive player pokemons -> we lost the duel

			if (won) {
				(*popponent).death_disappear(deltaTime);
			}
			else {
				(*pplayer).death_disappear(deltaTime);
			}

			//make gravity work 
			fall((*pplayer), groundY, deltaTime);
			fall((*popponent), groundY, deltaTime);
			//bullets that were shot before the end continue their movement
			(*pplayer).bullets.update(window, deltaTime, clock, elapsed, (*popponent).sprite, groundY);
			(*popponent).bullets.update(window, deltaTime, clock, elapsed, (*popponent).sprite, groundY);
			//draw stuff
			window.clear(sf::Color::Blue);
			window.draw(background);
			(*pplayer).draw(window);
			(*popponent).draw(window);


			window.draw(wonlost);
		}

		else if (state == 8) { //end of the fight against a wild pokemon

		if (won) {
			(*popponent).death_disappear(deltaTime);
		}
		else {
			(*pplayer).death_disappear(deltaTime);
		}
		//make gravity work 
		fall((*pplayer), groundY, deltaTime);
		fall((*popponent), groundY, deltaTime);
		//bullets that were shot before the end continue their movement
		(*pplayer).bullets.update(window, deltaTime, clock, elapsed, (*popponent).sprite, groundY);
		(*popponent).bullets.update(window, deltaTime, clock, elapsed, (*popponent).sprite, groundY);
		//draw stuff
		window.clear(sf::Color::Blue);
		window.draw(background);
		(*pplayer).draw(window);
		(*popponent).draw(window);

		window.draw(text_fainted);
		//to be completed

		} //wild opponent fainted


	window.display();
    }
    return 0;
}

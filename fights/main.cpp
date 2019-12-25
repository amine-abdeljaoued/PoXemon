#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Pokemon.h"
#include "Backpack.h"
#include "Backpack_Pokemon.cpp"
#include "Player.h"
#include "Opponent.h"
#include "Fight.h"




int main ()
{	// need a window and our boundaries (for moving up and down)
	sf::RenderWindow window(sf::VideoMode(1400, 700), "My window");
	float groundY = 300.0f; //Cannot go below this height - NB INITIALISE WITH WINDOW??
    float groundX = 1000.f;

	//intialise the backpack and players: NOT NEEDED IN ACTUAL MAIN, they will exist already
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

	Player* player = new Player(10.f, groundY, 200.f, 500.f, poke1);//by default, we take the first pokemon of the backpack
																			//do we want to be able to choose our pokemon at the beginning of the fight?
	Opponent* opponent = new Opponent(1000.f, groundY, 200.f, 800.f, opoke1);

	//ACTUAL MAIN: now for the fights...

	Fight fight(window);
	char mode = 't'; // this is decided before
	fight.initialise(mode, bag, opponent_bag, player, opponent, window);
	std::cout<<fight.bag.backpack_pokemons[0]-> health<<std::endl;

// ------------------------------------------------------------------------------------------------
	// run the program as long as the window is open
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				std::cout << "Goodbye" << std::endl;
				window.close();
			}
		}
		// Fights part ----------- 
		int i = fight.update(window);
		// window.draw(fight.popponent-> sprite);
		if(i!=1){
			// return to other state
			return 0;}

	window.display();
    }

	delete player;
	delete opponent;
    return 1;
}

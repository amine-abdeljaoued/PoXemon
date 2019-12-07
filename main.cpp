#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Pokemon.h"
#include "Pokeball.h"
#include "Bullet.h"
#include "Artillery.h"
#include "Backpack.h"
#include "Player.h"
#include "functions_state1.cpp"
#include "functions_state_5_6.cpp"
#include "Opponent.h"

float groundY = 300.0f; //Cannot go below this height
float groundX = 1000.f;

// We declare a variable "state" for fights which shows the game state
// 1 = start menu
// 2 = normal fight mode
// 3 = pokeball landed in centre -- to be implemented
// 4 = caught the pokemon
// 5 = we died -> choose another or quit

int main ()
{
	// Stuff used everywhere
	sf::Font font;
	if (!font.loadFromFile("upheavtt.ttf")) { std::cout << "could not load font" << std::endl; }
	else {font.loadFromFile("upheavtt.ttf");}

	Player eevee(10.f, groundY, 200.f, 500.f, 100, "Images/Pokemon_Images/vulari.png", 2, "Eevee");
	Opponent opponent1(1000.f,groundY,200.f, 800.f, 100, "Images/Pokemon_Images/urach.png", 2, "Opponent");
	eevee.set_enemy(&opponent1);
	opponent1.set_enemy(&eevee);
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
	intro_text.setString("You are about to fight " + opponent1.name);
	sf::Sprite opp = opponent1.sprite;
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
    
    Backpack bag;
	static int counter=0;
	int i = 0;

	//Objects needed for states 5, 6 :

	//buttons for pokemons -> in order to change player 
	//they should have : image, name, xp, life
	//button to leave the fight
	//some text elements

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
			
		}

		else if (state==2){
			// clear the window with black color - need to clear before drawing anything (overlap)
			eevee.update(deltaTime, window, clock_regenerate_bullets, elapsed, groundY);
			opponent1.update(deltaTime, window, clock_regenerate_bullets, elapsed, groundY);

			if (eevee.health.health <= 0) state = 5;
			if (opponent1.health.health <= 0) state = 6;

			bag.Pokeball_shoot(deltaTime, window, clock2, elapsed2);
			window.clear(sf::Color::Blue);
			window.draw(background);
			bag.draw(window);
			eevee.draw(window);
			opponent1.draw(window);
		}

		else if (state == 5) {
			//would be nice to have some animation to show that we are dead
			eevee.death_disappear(deltaTime);
			//make gravity work 
			fall(eevee, groundY, deltaTime);
			fall(opponent1, groundY, deltaTime);

			//bullets that were shot before the end continue their movement
			//small detail to be changed : the player's bullet bar should not be updated anymore
			eevee.bullets.update(deltaTime, clock, elapsed, opponent1.sprite, groundY);
			opponent1.bullets.update(deltaTime, clock, elapsed, opponent1.sprite, groundY);

			window.clear(sf::Color::Blue);
			window.draw(background);
			eevee.draw(window);
			opponent1.draw(window);


			//if we are against a wild pokemon :
				// choose another pokemon / leave the fight
				//initiaize, destruct stuff and go back to state 2 / go back to map

			//if we are against a trainer :
				//if you have other pokemons
					//choose your pokemon 
					//(trainer chooses another pokemon ?)
					//initiaize, destruct stuff and go back to state 2
				//else
					//the trainer won
					//lost money
					//gained xp (that should depend on the level of the pokemon)
					//go back directly to the shop (as all our pokemons are dead)

		}

		else if (state == 6) {
			opponent1.death_disappear(deltaTime);
			fall(eevee, groundY, deltaTime);
			fall(opponent1, groundY, deltaTime);
			eevee.bullets.update(deltaTime, clock, elapsed, opponent1.sprite, groundY);
			opponent1.bullets.update(deltaTime, clock, elapsed, opponent1.sprite, groundY);

			window.clear(sf::Color::Blue);
			window.draw(background);
			eevee.draw(window);
			opponent1.draw(window);

			//if we are against a wild pokemon :
				// you won against ... !
				// gained xp 
				// go back to map

			//if we are against a trainer :
				//if the trainer has other pokemons
					//next pokemon to fight : '...'
					//choose your pokemon / leave the fight (without money)
					//initiaize, destruct stuff and go back to state 2 / go back to map
				//else
					//you won against the trainer.
					//gained money
					//gained xp
					//go back to map

		}

		//std::cout << counter++ << std::endl;
		
		window.display();
    }
    return 0;
}

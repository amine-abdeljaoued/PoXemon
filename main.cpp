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

	// Objects for state 2:
	float deltaTime = 0.0f;

    sf::Clock clock;
    sf::Clock clock_regenerate_bullets;
    sf::Time elapsed;
    
    sf::Clock clock2;
    sf::Time elapsed2;
    
    Backpack bag;
	static int counter=0;
	int i = 0;
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
			std::cout<<i<<std::endl;
			state = update_state1(window, start_button, info_button, star);
			window.clear(sf::Color::Blue);
			window.draw(background);
			draw1(window, start_button, info_button, start_text, info_text, intro_text, opp, star);
			
		}

		else if (state==2){
			// clear the window with black color - need to clear before drawing anything (overlap)
			eevee.update(deltaTime, window, clock_regenerate_bullets, elapsed, groundY);
			opponent1.update(deltaTime, window, clock_regenerate_bullets, elapsed, groundY);

			bag.Pokeball_shoot(deltaTime, window, clock2, elapsed2);
			window.clear(sf::Color::Blue);
			window.draw(background);
			bag.draw(window);
			eevee.draw(window);
			opponent1.draw(window);
		}

		//std::cout << counter++ << std::endl;
		
		window.display();
    }
    return 0;
}

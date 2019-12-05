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

#include "Opponent.h"

float groundY = 300.0f; //Cannot go below this height
float groundX = 1000.f;

void initialise_background(sf::RenderWindow& window, std::string path, sf::Sprite& background, sf::Texture& texture){
	// Function that sets up our background to be the same size as the window
	// Need to initialise the sprite and texture of the background before though
	sf::Vector2u TextureSize;  //Added to store texture size.
	sf::Vector2u WindowSize;   //Added to store window size.

	if(!texture.loadFromFile(path)){std::cout<<"Background didn't load"<<std::endl;}
	else
	{
		TextureSize = texture.getSize(); 	//Get size of texture.
		WindowSize = window.getSize();      //Get size of window.

		float ScaleX = (float) WindowSize.x / TextureSize.x;
		float ScaleY = (float) WindowSize.y / TextureSize.y;     //Calculate scale.

		background.setTexture(texture);
		background.setScale(ScaleX, ScaleY);      //Set scale.
  	}
}

// We declare a global variable for fights which shows the game state
// 1 = start menu
// 2 = normal fight mode
// 3 = pokeball landed in centre -- to be implemented
// 4 = caught the pokemon
// 5 = we died -> choose another or quit
// 6 = opponent dies
int state = 2;


int main ()
{
	Player eevee(10.f, groundY, 200.f, 500.f, 100, "Images/Pokemon_Images/vulari.png", 2, "Eevee");
	Opponent opponent1(1000.f,groundY,200.f, 800.f, 100, "Images/Pokemon_Images/urach.png", 2, "Opponent");
	eevee.set_enemy(&opponent1);
	opponent1.set_enemy(&eevee);

    sf::RenderWindow window(sf::VideoMode(1400, 700), "My window");

	if (state==1){
		//...
	}
	
	if (state == 2){
		sf::Texture BackgroundTexture;
		sf::Sprite background;
		initialise_background(window, "Images/grassbg.png", background, BackgroundTexture);

		float deltaTime = 0.0f;

		sf::Clock clock;
		sf::Clock clock_regenerate_bullets;
		sf::Time elapsed;

		sf::Clock clock2;
		sf::Time elapsed2;

		Backpack bag;
		static int counter=0;

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

			// clear the window with black color - need to clear before drawing anything (overlap)
			eevee.update(deltaTime, window, clock_regenerate_bullets, elapsed, groundY);
			opponent1.update(deltaTime, window, clock_regenerate_bullets, elapsed, groundY);

			bag.Pokeball_shoot(deltaTime, window, clock2, elapsed2);
			window.clear(sf::Color::Blue);
			window.draw(background);
			bag.draw(window);
			eevee.draw(window);
			opponent1.draw(window);

			//std::cout << counter++ << std::endl;

			window.display();
		}
    }
    return 0;
}

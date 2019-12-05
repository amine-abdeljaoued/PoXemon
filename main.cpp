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

int main ()
{
    sf::RenderWindow window(sf::VideoMode(1400, 700), "My window");

	// -----------------------------------------------------------------
	// This gives us a background that is the same size as the window
	sf::Texture BackgroundTexture;
	sf::Sprite background;
	sf::Vector2u TextureSize;  //Added to store texture size.
	sf::Vector2u WindowSize;   //Added to store window size.

	if(!BackgroundTexture.loadFromFile("Images/grassbg.png")){
                std::cout<<"BG didn't load"<<std::endl;
	}
	else
	{
		TextureSize = BackgroundTexture.getSize(); //Get size of texture.
		WindowSize = window.getSize();             //Get size of window.

		float ScaleX = (float) WindowSize.x / TextureSize.x;
		float ScaleY = (float) WindowSize.y / TextureSize.y;     //Calculate scale.

		background.setTexture(BackgroundTexture);
		background.setScale(ScaleX, ScaleY);      //Set scale.  
  	}
	// -----------------------------------------------------------------

	
	Player eevee(10.f, groundY, 200.f, 500.f, 100, "Images/Pokemon_Images/rhykarp.png", 2, "Eevee"); // this should be initialized as the pokemon we clicked on.
	Opponent opponent1(1000.f,groundY,200.f, 800.f, 100, "Images/Pokemon_Images/raporoy.png", 2, "Opponent");
	eevee.set_enemy(&opponent1);
	opponent1.set_enemy(&eevee);

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
    return 0;
}

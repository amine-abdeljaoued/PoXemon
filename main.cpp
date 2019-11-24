#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Pokemon.h"
#include "Pokeball.h"
#include "Bullet.h"
#include "Artillery.h"
#include "Backpack.h"

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

    Pokemon eevee(10.f, groundY, 200.f, 500.f);
    float deltaTime = 0.0f;

    sf::Clock clock;
    sf::Clock clock_regenerate_bullets;
    sf::Time elapsed;
    
    Backpack bag;

	// run the program as long as the window is open
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		elapsed = clock_regenerate_bullets.getElapsedTime();

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
        eevee.update(deltaTime, window, clock_regenerate_bullets, elapsed);
	 	bag.Pokeball_shoot(deltaTime, window);
		window.clear(sf::Color::Blue);
		window.draw(background);
        bag.draw(window);
        eevee.draw(window);

		window.display();
    }
    return 0;
}

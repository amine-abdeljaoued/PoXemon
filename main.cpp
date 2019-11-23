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
    //video mode defines the size of the window
    //constructor accepts a third optional argument: a style (decorations and features)
    //see https://www.sfml-dev.org/tutorials/2.5/window-window.php

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
        bag.draw(window);
        eevee.draw(window);

		window.display();
    }
    return 0;
}

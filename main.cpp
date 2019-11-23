#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Pokemon.h"
#include "Pokeball.h"
#include "Bullet.h"
#include "Artillery.h"

float groundY = 300.0f; //Cannot go below this height
float groundX = 1000.f;

int main ()
{
	sf::RenderWindow window(sf::VideoMode(1400, 700), "My window");
	//video mode defines the size of the window
	//constructor accepts a third optional argument: a style (decorations and features)
	//see https://www.sfml-dev.org/tutorials/2.5/window-window.php

	Pokemon eevee(10.0f, groundY, 200.f, 500.f);
	float deltaTime = 0.0f;

	sf::Clock clock;

	sf::Clock clock_regenerate_bullets;
	sf::Time elapsed;

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

		window.clear(sf::Color::Blue);

		// clear the window with black color - need to clear before drawing anything (overlap)
		eevee.update(deltaTime, window, clock_regenerate_bullets, elapsed);
		window.clear(sf::Color::Blue);
		eevee.draw(window);

		
		/* //std::cout << elapsed.asSeconds() << std::endl;
		if (elapsed.asSeconds() > 2.0f && eevee.available_bullets < eevee.max_available_bullets) {
			eevee.available_bullets += 1;
			std::cout << eevee.available_bullets << std::endl;
			std::cout << "adding a bullet" << std::endl;
			clock_regenerate_bullets.restart();
		} */

		// end the current frame - mandatory: takes what was drawn since the last call to display and displays it on the window
		window.display();

	}
	return 0;
}

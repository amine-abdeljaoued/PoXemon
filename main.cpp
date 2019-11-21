#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Pokemon.h"
#include "Pokeball.h"
#include "Bullet.h"

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

	// run the program as long as the window is open
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
			{
				std::cout << "Goodbye" << std::endl;
				window.close();
			}
		}

		window.clear(sf::Color::Blue);


		// clear the window with black color - need to clear before drawing anything (overlap)
		eevee.update(deltaTime, window);
		eevee.update_bullets(deltaTime);
		window.clear(sf::Color::Blue);
		window.draw(eevee.sprite);

		if (eevee.shooting) {
			window.draw(eevee.ball.ball);
		}

		for (unsigned i = 0; i < eevee.bullets.size(); i++) {
			window.draw(eevee.bullets[i].bullet);
		}

		// end the current frame - mandatory: takes what was drawn since the last call to display and displays it on the window
		window.display();

	}
	return 0;
}

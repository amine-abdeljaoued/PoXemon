#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Window.hpp>


void main(int argc, char** argv[]) {
	sf::RenderWindow window(sf::VideoMode(880, 720), "Pokedex?");

	sf::Texture PokedexTexture;
	PokedexTexture.loadFromFile("test.png");

	sf::Sprite Pokedex(PokedexTexture);



	Pokedex.setOrigin(0.f,0.f);


	sf::Texture ArrowsTexture;
	ArrowsTexture.loadFromFile("arrows.png");
	sf::Sprite Arrows(ArrowsTexture);
	Arrows.setOrigin(-700.f, -260.f);


	sf::Texture element_air;
	element_air.loadFromFile("element_air.png");
	sf::Sprite Air(element_air);
	Air.setOrigin(-730.f, -40.f);

	sf::Texture element_earth;
	element_earth.loadFromFile("element_earth.png");
	sf::Sprite Earth(element_earth);
	Earth.setOrigin(-730.f, -560.f);


	int element = 0;


	sf::Vector2f increment(0.f, 240.f);



	while (window.isOpen()) {
		sf::Event event;
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i position = sf::Mouse::getPosition(window);
				
				//arrows
				if (760 <= position.x && position.x <= 840) {
					if (280 <= position.y && position.y <= 360) { //up
						if (Pokedex.getPosition().y + increment.y < 1) {
							Pokedex.setPosition(Pokedex.getPosition() + increment);
						}
					}
					else if (360 <= position.y && position.y <= 440) { //down
						Pokedex.setPosition(Pokedex.getPosition() - increment);
						
					}

					else if (40 <= position.y && position.y <= 150) {
						std::cout << "air" << '\n';
					}

					else if (560 <= position.y && position.y <= 690) {
						std::cout << "earth" << '\n';
					}
				}


				


				
			}
			
		}
		
		//mushroom.setPosition(mushroom.getPosition() + increment);
		//increment.y = 0.f;

		window.clear(sf::Color(16, 16, 16, 255)); // Dark gray.
		window.draw(Pokedex); // Drawing our sprite.
		window.draw(Arrows);

		window.draw(Air);
		window.draw(Earth);
		window.display();

		
	}
}

/*
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //up
		{
			increment.y = 4;
			if (mushroom.getPosition().y + increment.y > 0) {
				increment.y = 0.f;
			}
			
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //up
		{
			increment.y = -4;
			
		}
*/

/*
			else if (event.type == sf::Event::MouseWheelMoved)
			{
				std::cout << event.mouseWheel.delta << '\n';
				increment.y = event.mouseWheel.delta;
				increment.y = increment.y / 50;
			}
			*/

/*
	float gridSizeF = 100.f;
	unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
	float dt = 0.f;
	sf::Clock dtClock;

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");


	sf::View view;
	view.setSize(1920.f, 1080.f);
	view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);
	float viewSpeed = 300.f;

	sf::RectangleShape shape(sf::Vector2f(gridSizeF, gridSizeF));

	while (window.isOpen())
	{
		dt = dtClock.restart().asSeconds();


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			view.move(viewSpeed*dt, 0.f);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			view.move(-viewSpeed * dt, 0.f);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			view.move(0.f, viewSpeed * dt);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			view.move(0.f, -viewSpeed * dt);
		}



		window.clear();
		window.setView(view);

		window.draw(shape);

		window.setView(window.getDefaultView());


		window.display();
	}
	*/
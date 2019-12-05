#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Window.hpp>


void main(int argc, char** argv[]) {
	sf::RenderWindow window(sf::VideoMode(880, 720), "Pokedex?");

	sf::Texture PokedexTexture;
	PokedexTexture.loadFromFile("pokedex.png");
	sf::Sprite Pokedex(PokedexTexture);

	Pokedex.setOrigin(0.f,0.f);

	sf::Texture ArrowsTexture;
	ArrowsTexture.loadFromFile("arrows.png");
	sf::Sprite Arrows(ArrowsTexture);
	Arrows.setOrigin(-700.f, -260.f);

	sf::Texture element_air;
	element_air.loadFromFile("element_air.png");
	sf::Sprite Air(element_air);
	
	sf::Texture element_earth;
	element_earth.loadFromFile("element_earth.png");
	sf::Sprite Earth(element_earth);
	
	sf::Texture element_fire;
	element_fire.loadFromFile("element_fire.png");
	sf::Sprite Fire(element_fire);

	sf::Texture element_water;
	element_water.loadFromFile("element_water.png");
	sf::Sprite Water(element_water);


	int element = 0;


	sf::Vector2f increment(0.f, 240.f);
	sf::Vector2f increment_big(0.f, 1440.f);
	sf::Vector2f increment_medium(0.f, 480.f);
	sf::Vector2f transition(880.f, 0.f);
	sf::Vector2f big_transition(3520.f, 0.f);
	sf::Vector2f temp(0.f, 0.f);


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
						else {
							if (element == 0 || element == 1) {Pokedex.setPosition(Pokedex.getPosition() - increment_big);}
							else {Pokedex.setPosition(Pokedex.getPosition() - increment_medium);}
						}
					}
					else if (360 <= position.y && position.y <= 440) { //down
						Pokedex.setPosition(Pokedex.getPosition() - increment);
						if (element == 0 || element == 1) {
							if (Pokedex.getPosition().y - increment.y < -increment_big.y -240) {Pokedex.setPosition(Pokedex.getPosition() + increment_big + increment);}
						}
						else {
							if (Pokedex.getPosition().y - increment.y < -increment_medium.y - 240) {Pokedex.setPosition(Pokedex.getPosition() + increment_medium + increment);}
						}
						
					}

					else if (40 <= position.y && position.y <= 150) { //next element
						element = element + 1;
						temp.x = Pokedex.getPosition().x - transition.x;
						Pokedex.setPosition(temp);
						if (element == 4) {
							element = 0;
							temp.x = Pokedex.getPosition().x + big_transition.x;
							Pokedex.setPosition(temp);
						}
					}

					else if (560 <= position.y && position.y <= 690) {
						element = element - 1;
						temp.x = Pokedex.getPosition().x + transition.x;
						Pokedex.setPosition(temp);
						if (element == -1) {
							element = 3;
							temp.x = Pokedex.getPosition().x - big_transition.x;
							Pokedex.setPosition(temp);
						}
					}
				}


				


				
			}
			
		}
		
		//mushroom.setPosition(mushroom.getPosition() + increment);
		//increment.y = 0.f;

		window.clear(sf::Color(16, 16, 16, 255)); // Dark gray.
		window.draw(Pokedex); // Drawing our sprite.
		window.draw(Arrows);

		if (element == 0) {
			Fire.setOrigin(-730.f, -40.f);
			Water.setOrigin(-730.f, -560.f);
			window.draw(Fire);
			window.draw(Water);
		}
		else if (element == 1) {
			Air.setOrigin(-730.f, -40.f);
			Earth.setOrigin(-730.f, -560.f);
			window.draw(Air);
			window.draw(Earth);
		}
		else if (element == 2) {
			Water.setOrigin(-730.f, -40.f);
			Fire.setOrigin(-730.f, -560.f);
			window.draw(Water);
			window.draw(Fire);
		}
		else {
			Earth.setOrigin(-730.f, -40.f);
			Air.setOrigin(-730.f, -560.f);
			window.draw(Earth);
			window.draw(Air);
		}

		window.display();

		
	}
}
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <string>
#include <SFML/Window.hpp>

void main(int argc, char** argv[]) {

	sf::RenderWindow window(sf::VideoMode(1400, 700), "My window");

	sf::Texture super_rock_1;
	super_rock_1.loadFromFile("Rock_Super_1.png");

	sf::Sprite Super_Rock_1a(super_rock_1);
	

	Super_Rock_1a.setScale(sf::Vector2f(2.f, 2.f));
	

	Super_Rock_1a.setOrigin(-300.f, -300.f);
	

	sf::Vector2f incrementa(0.f, 2.f);
	sf::Vector2f mult(0, 1.1);		

	sf::Vector2f end(700.f, 0.f);
	int counter = 0;

	bool attack = false;

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					attack = true;
				}
			}
		}

		if (attack) {
			
			if (Super_Rock_1a.getPosition().y < -650) {
				incrementa = -incrementa;
				//Super_Rock_1a.setPosition(-60.f, -100.f);
				//counter = counter + 1;
				//if (counter == 4) { attack = false; }
				
			}
			
			Super_Rock_1a.setPosition(Super_Rock_1a.getPosition() - incrementa);
			incrementa.y = incrementa.y * 1.02;
			std::cout << Super_Rock_1a.getPosition().y << std::endl;
			
		}
			

		window.clear(sf::Color(16, 16, 16, 255)); // Dark gray.
		window.draw(Super_Rock_1a);
		
		window.display();


	}
}

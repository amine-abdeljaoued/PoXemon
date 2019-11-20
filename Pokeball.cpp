
#include "Pokeball.h"



	Pokeball::Pokeball() {   // Thing to add: should also initialise ball                                            image, with views for rotation
		sf::Texture pic;
		pic.loadFromFile("pokeball.png");
		ball.setTexture(pic);
		ball.setScale(sf::Vector2f(0.4f, 0.4f));
	}
	void Pokeball::dissapear() {
		ball.setPosition(500.f, 2000.f);
		// I just set this randomly, we must figure out if we wan't to delete the balls, keep them in pokemon class/etc...
	}
	void Pokeball::setPosition(float& xpos, float& ypos) {
		x = xpos;
		y = ypos;
		ball.setPosition(xpos, ypos);
	}
	bool Pokeball::update(float deltaTime) {
		velocityY += gravity * deltaTime;
		x += velocityX * deltaTime;
		y += velocityY * deltaTime;

		float groundX = 1000.f;
		setPosition(x, y);
		if (x >= groundX) {     // Ball off the screen, we want to remove it from                               visible, to avoid any complications
			dissapear();
			return false;
		}
		return true;
	}



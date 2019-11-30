#include "Pokemon.h"

Pokemon::Pokemon(float xstart, float ystart, float h, float v, float hp, std::string path, float pokemon_rarity)
{
	rarity = pokemon_rarity; //1 == common, 2 == rare, 3 == epic, 4 == legendary

	health.setHealth(hp); 		// Pokemon starts with full health when it is created
	health.setPosition(xstart+50, ystart-250);
	velocityX = 0.0f;
	velocityY = 0.0f;
	jumpHeight = h;
	speed = v;
	canJump = true;
	shooting = false;
	x = xstart;
	y = ystart;
	sprite.setPosition(sf::Vector2f(x, y));

			if (!pic.loadFromFile(path)){ std::cout << "could not load" << std::endl;} //path = Images/eevee.png
	pic.loadFromFile(path);
	sprite.setTexture(pic);
	sprite.setScale(sf::Vector2f(0.4f, 0.4f));
}


void Pokemon::draw(sf::RenderTarget& target) {//const ?
	target.draw(sprite);
	health.draw(target);
	bullets.draw(target);
	bullets.bulletbar.draw(target);
}
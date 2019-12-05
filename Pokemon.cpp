#include "Pokemon.h"

Pokemon::Pokemon(float xstart, float ystart, float h, float v, float hp, std::string path, float pokemon_rarity, std::string pname)
{
	rarity = pokemon_rarity; //1 == common, 2 == rare, 3 == epic, 4 == legendary
	name = pname;
	health.setHealth(hp); 		
	health.setPosition(xstart+50, ystart-250);
	health.name = name;
	health.level = level;

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
	//set the x origin at the middle
	//useful when we flip (mirror image) the sprite with update_sprite_orientation (in the player class)
	//indeed the sprites are flipped wrt the origin so it doesn't look good if it's not at the middle.
	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, 0));
}

void Pokemon::set_enemy(Pokemon* enemy) {
	this->enemy = enemy;
}



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
	//also useful for death_dissapear()
	//these functions both scale sprites, which is is done wrt the origin so if it is not set at center, it won't look nice
	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2));

}

void Pokemon::set_enemy(Pokemon* enemy) {
	this->enemy = enemy;
}


void Pokemon::death_disappear(float& deltaTime) {//to improve

	float total_time = 0.3; 
	float initial_scale = 0.5;
	float new_x;

	//scale it down until zero
	if (sprite.getScale().y > 0) {
		if (sprite.getScale().x < 0) {
			new_x = sprite.getScale().x + (deltaTime / total_time) * initial_scale;
		}
		if (sprite.getScale().x > 0) {
			new_x = sprite.getScale().x - (deltaTime / total_time) * initial_scale;
		}

		float new_y = sprite.getScale().y - (deltaTime / total_time) * initial_scale;
		sprite.setScale(new_x, new_y);
	}

	//now a little animation of 'implosion' ?

}


//#pragma once
#include "Bullet_bar.h"



BulletBar::BulletBar() {

	//load the picture
	//to do : should be the same as the bullet our pokemon has
	if (!bullet_pic.loadFromFile("Images/red_bullet.png")) { std::cout << "could not load" << std::endl; }
	bullet_pic.loadFromFile("Images/red_bullet.png");
	bullet_sprite.setTexture(bullet_pic);
	bullet_sprite.setScale(sf::Vector2f(0.15, 0.15));

	available_bullets = 20; //at the begginning, we start with max_available_bullets (same as in artillery)
	empty_part = 0;

	//initialize the text (string of numbers representing the available bullets)
	//link for the font: https://www.dafont.com/fr/upheaval.font
	//(We might change the font later)
	if (!font.loadFromFile("upheavtt.ttf")) { std::cout << "could not load bullet_bar font" << std::endl; }
	nb_text.setFont(font);
	nb_text.setCharacterSize(20);
	nb_text.setString(std::to_string(available_bullets));

	xpos = 200;
	ypos = 150;
	setPosition(xpos, ypos);//might change it 

}

void BulletBar::setPosition(float x, float y) {
	//set origins at center to make it easier to manipulate

	bullet_sprite.setOrigin(sf::Vector2f(bullet_sprite.getGlobalBounds().width / 2, bullet_sprite.getGlobalBounds().height / 2));
	bullet_sprite.setPosition(x, y);
	//now set the position of the text at the center of the ball
	nb_text.setOrigin(sf::Vector2f(nb_text.getGlobalBounds().width / 2, nb_text.getGlobalBounds().height / 2));
	nb_text.setPosition(x+bullet_sprite.getGlobalBounds().width/2, y + bullet_sprite.getGlobalBounds().height*0.3);//just found numbers that 'look' good
}

void BulletBar::update(int additional_bullet) {

	available_bullets += additional_bullet;
	nb_text.setString(std::to_string(available_bullets));
	//std::cout << available_bullets << std::endl;

	//this does not work

	//empty_part += additional_bullet*bullet_sprite.getGlobalBounds().height / 20; //increase of decrease the size of the empty_part
	//float w = bullet_sprite.getGlobalBounds().width;
	//float h = bullet_sprite.getGlobalBounds().height - empty_part;
	//sf::IntRect empty_rect(0, 0, w, h);

	//bullet_sprite.setTexture(bullet_pic);
	//bullet_sprite.setTextureRect(empty_rect);
}

void BulletBar::draw(sf::RenderWindow& target){
	target.draw(bullet_sprite);
	target.draw(nb_text);
}

void BulletBar::draw(sf::RenderWindow& target, sf::Shader* shader){
	target.draw(bullet_sprite, shader);
	target.draw(nb_text, shader);
}
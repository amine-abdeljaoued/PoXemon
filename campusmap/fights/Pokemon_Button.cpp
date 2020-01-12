#include "Pokemon_Button.h"


Pokemon_Button::Pokemon_Button(std::string& name, int& lvl, int& h, int& i) {

	index = i; //index of the corresponding backpack pokemon
	level = lvl;

	//used for placement
	/*red_circle.setRadius(5);
	red_circle.setFillColor(sf::Color(255, 0, 0));*/

	//Text
	if (!font.loadFromFile("fights/upheavtt.ttf")) { std::cout << "could not  pokemon button font" << std::endl; }
	font.loadFromFile("fights/upheavtt.ttf");
	name_text.setCharacterSize(35);
	level_text.setCharacterSize(25);
	name_text.setFillColor(sf::Color::Black);
	level_text.setFillColor(sf::Color::Black);
	name_text.setString(name);
	level_text.setString("lvl: " + std::to_string(lvl));

	//Background bar with name, level, etc...
	if (!bar_pic.loadFromFile("fights/Images/bar.png")) { std::cout << "could not load" << std::endl; }
	bar_pic.loadFromFile("fights/Images/bar.png");
	bar.setTexture(bar_pic);
	bar.setScale(sf::Vector2f(0.2, 0.2));


	//Little heart next to bar - numbers used just work, don't know how to make them nice
	if (!heart_pic.loadFromFile("fights/Images/heart.png")) { std::cout << "could not load" << std::endl; }
	heart_pic.loadFromFile("fights/Images/heart.png");
	heart.setTexture(heart_pic);
	heart.setScale(sf::Vector2f(0.55, 0.55));

	//pokemon sprite
	//initialize it using the name
	if (!pokemon_pic.loadFromFile("fights/Images/Pokemon_Images/"+name+".png")) { std::cout << "could not load" << std::endl; } //path = Images/eevee.png
	pokemon_pic.loadFromFile("fights/Images/Pokemon_Images/" + name + ".png");
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	sprite.setTexture(pokemon_pic);
	sprite.scale(0.3, 0.3);

	//Size of outline and bar must be initialised to the same size, later bar will change
	//Outline with white base
	health = h;
	healthwidth = 120;
	healthheight = 15;
	outline.setFillColor(sf::Color::White);
	outline.setOutlineThickness(4);
	outline.setOutlineColor(sf::Color::Black);
	outline.setSize(sf::Vector2f(120, 15));

	//bar that shows the health
	healthbar.setSize(sf::Vector2f(health * healthwidth / 100, healthheight));
	//Bar changes from green to red as health decreases
	if (health > 50) {
		healthbar.setFillColor(sf::Color((100 - health) * 2.55 * 2, 255, 0));
	}
	else {
		healthbar.setFillColor(sf::Color(255, health * 2.55 * 2, 0));
	}
    // Both bars and the heart must move together

	bar.setOrigin(bar.getLocalBounds().width / 2, bar.getLocalBounds().height / 2);
	name_text.setOrigin(name_text.getLocalBounds().width / 2, name_text.getLocalBounds().height / 2);
	level_text.setOrigin(level_text.getLocalBounds().width / 2, level_text.getLocalBounds().height / 2);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

void Pokemon_Button::setHealth(int& a) {
	health = a;
	update();
}

void Pokemon_Button::Levelup() {
	level++;
	level_text.setString("lvl: " + std::to_string(level));
}

void Pokemon_Button::update() {
	//update the healthbar
	healthbar.setSize(sf::Vector2f(health * healthwidth / 100, healthheight));

	if (health > 50) {
		healthbar.setFillColor(sf::Color((100 - health) * 2.55 * 2, 255, 0));
	}
	else {
		healthbar.setFillColor(sf::Color(255, health * 2.55 * 2, 0));
	}
	//update the color and clickability if the pokemon is dead
	if (health == 0) {//make it vary dark to know we cannont click
		bar.setColor(sf::Color(100, 100, 100));
		sprite.setColor(sf::Color(50, 50, 50));
		healthbar.setFillColor(sf::Color(50, 50, 50));
		heart.setColor(sf::Color(50,50,50));
		outline.setFillColor(sf::Color(50, 50, 50));
	}

}



void Pokemon_Button::setPosition(float x, float y) {



	// Background
	bar.setPosition(x, y);

	//Text
	name_text.setPosition(x - bar.getGlobalBounds().width*2/5 , y -bar.getGlobalBounds().height/2);

	// Health bar + level
	float x1 = x + bar.getGlobalBounds().width / 2;
	float y1 = y + bar.getGlobalBounds().height * 3 / 5;

	level_text.setPosition(x - bar.getGlobalBounds().width*2/5 , y );
	outline.setPosition(x, y + bar.getGlobalBounds().height / 10);
	healthbar.setPosition(x , y + bar.getGlobalBounds().height / 10);
	heart.setPosition(x-20, y+3);           // Heart slightly left and up to the bar (random choice, works well)

	sprite.setPosition(x- bar.getGlobalBounds().width*3/4, y);

	//red_circle.setPosition(bar.getPosition());
}


void Pokemon_Button::update_mouse(sf::Vector2f& mouse_pos, int& clicked_button) {
	//when the mouse is on the button (not clicked), have a red contour, and make the pokemon jump
	if (health > 0) {
		if (bar.getGlobalBounds().contains(mouse_pos)) {//check if the mouse is on a pokemon button
			bar.setColor(sf::Color(255, 99, 99));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				std::cout << "you pressed the button" << std::endl;
				clicked_button = index; //value changes if we click
			}
		}
		else {
			bar.setColor(sf::Color(255, 255, 255));
		}
	}
	else
	{//heath==0
		if (bar.getGlobalBounds().contains(mouse_pos)) {//check if the mouse is on a pokemon button
			bar.setColor(sf::Color(60, 60, 60));
		}
		else {
			bar.setColor(sf::Color(100, 100, 100));
		}
	}
}

void Pokemon_Button::draw(sf::RenderWindow& target) {

	// Object drawn last is on top
	bar.setTexture(bar_pic);
	target.draw(bar);
	target.draw(outline);
	target.draw(healthbar);
	heart.setTexture(heart_pic);//need yo reset the sprite for some reason
	target.draw(heart);
	//for some reason i have to reset the font every time otherwise it throws an exception.
	//I would be better to find an other solution
	level_text.setFont(font);
	name_text.setFont(font);
	target.draw(level_text);
	target.draw(name_text);

	sprite.setTexture(pokemon_pic);
	target.draw(sprite);

	//target.draw(red_circle);
}

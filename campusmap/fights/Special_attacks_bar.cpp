
#include "Special_Attacks_bar.h"

Special_Attacks_Bar::Special_Attacks_Bar() {
	attack1_available = true;
	attack1_time = 3; // We initialise how long these take - arbitrary
	regeneration1_time = 3;
	shooting1 = false;
	shooting2 = false;
	shooting3 = false;
	regenerating1 = false;

}

void Special_Attacks_Bar::initialise(sf::RenderWindow& window){

    // Load images into our sprites
	if (!key1_texture.loadFromFile("fights/Images/Special_Attacks_Bar/key1.png")) { std::cout << "could not load key1" << std::endl; }

	if (type == 10){ // type earth
		if (!attack_1_texture_bw.loadFromFile("fights/Images/Special_Attacks_Bar/rock_bw.png")) { std::cout << "could not load rock bw" << std::endl;}; 
		attack_1_texture_bw.loadFromFile("fights/Images/Special_Attacks_Bar/rock_bw.png");
		if (!attack_1_texture.loadFromFile("fights/Images/Special_Attacks_Bar/rock.png")) { std::cout << "could not load rock" << std::endl;} 
		attack_1_texture.loadFromFile("fights/Images/Special_Attacks_Bar/rock.png");
	};
	if (type == 20){ // type water
		if (!attack_1_texture_bw.loadFromFile("fights/Images/Special_Attacks_Bar/water_bw.png")) { std::cout << "could not load water bw" << std::endl;}; 
		attack_1_texture_bw.loadFromFile("fights/Images/Special_Attacks_Bar/water_bw.png");
		if (!attack_1_texture.loadFromFile("fights/Images/Special_Attacks_Bar/water.png")) { std::cout << "could not load water" << std::endl;}; 
		attack_1_texture.loadFromFile("fights/Images/Special_Attacks_Bar/water.png");
	};
	if (type == 30){ // type air
		if (!attack_1_texture_bw.loadFromFile("fights/Images/Special_Attacks_Bar/air_bw.png")) { std::cout << "could not load air bw" << std::endl;}; 
		attack_1_texture_bw.loadFromFile("fights/Images/Special_Attacks_Bar/air_bw.png");
		if (!attack_1_texture.loadFromFile("fights/Images/Special_Attacks_Bar/air.png")) { std::cout << "could not load air" << std::endl;}; 
		attack_1_texture.loadFromFile("fights/Images/Special_Attacks_Bar/air.png");
	};
	if (type == 40){ // type fire
		if (!attack_1_texture_bw.loadFromFile("fights/Images/Special_Attacks_Bar/fire_bw.png")) { std::cout << "could not load fire bw" << std::endl;}; 
		attack_1_texture_bw.loadFromFile("fights/Images/Special_Attacks_Bar/fire_bw.png");
		if (!attack_1_texture.loadFromFile("fights/Images/Special_Attacks_Bar/fire.png")) { std::cout << "could not load fire" << std::endl;}; 
		attack_1_texture.loadFromFile("fights/Images/Special_Attacks_Bar/fire.png");
	};

    // Set textures
	key1.setTexture(key1_texture);
	attack_1_sprite.setTexture(attack_1_texture);
	
	// Set scales according to window size
	sf::Vector2u TextureSize1 = key1_texture.getSize(); 	//Get size of texture.
	sf::Vector2u TextureSize2 = attack_1_texture.getSize();
	sf::Vector2u WindowSize = window.getSize();      //Get size of window.

	float ScaleKey = (float) WindowSize.y / TextureSize1.y; //Calculate scale.
	float ScaleSprite = (float) WindowSize.y / TextureSize2.y;

	key1.setScale(ScaleKey/14,ScaleKey/14);	//Set scale.  
	attack_1_sprite.setScale(ScaleSprite/7, ScaleSprite/7);
	
	// Set up rectangles
	boxsize = window.getSize().y/7; // NB CHANGE ACCORDING TO WINDOW SIZE
    base_rect.setFillColor(sf::Color(192,192,192)); 
    base_rect.setOutlineThickness(4);
    base_rect.setOutlineColor(sf::Color::Black);
    base_rect.setSize(sf::Vector2f(boxsize,boxsize));
    timer_rect.setFillColor(sf::Color(114, 228, 110)); // green: available
    timer_rect.setSize(sf::Vector2f(boxsize,boxsize));

	// Change origins
	attack_1_sprite.setOrigin(sf::Vector2f(attack_1_sprite.getLocalBounds().width / 2, attack_1_sprite.getLocalBounds().height / 2));
	key1.setOrigin(sf::Vector2f(key1.getGlobalBounds().width / 2, key1.getGlobalBounds().height / 2));

	// Set position - ACCORDING TO WINDOW SIZE
	xpos = 100;
	ypos = 550;
	setPosition(xpos, ypos);//might change it 

}

void Special_Attacks_Bar::setPosition(float x, float y) {
	base_rect.move(x, y);
	timer_rect.move(x, y);
	attack_1_sprite.setPosition(x + base_rect.getGlobalBounds().width / 2, y + base_rect.getGlobalBounds().height / 2);
	
	// Set the key to be centered at the top right of the base rectangle
	key1.setPosition(base_rect.getPosition().x , base_rect.getPosition().y );
	key1.move(sf::Vector2f(key1.getGlobalBounds().width / 2, key1.getGlobalBounds().height / 2));
}

void Special_Attacks_Bar::initial_state(){
	base_rect.setFillColor(sf::Color(192,192,192)); // grey
    base_rect.setSize(sf::Vector2f(boxsize,boxsize));
    timer_rect.setFillColor(sf::Color(114, 228, 110)); 	// green
    timer_rect.setSize(sf::Vector2f(boxsize,boxsize));
	attack_1_sprite.setTexture(attack_1_texture);
	attack1_available = true;
}

void Special_Attacks_Bar::update1(sf::Clock& clock1) {
	/* The idea:
	We want the timer bar to grow upwards as we use time, and shrink downwards as its regenerating
	To do this we make the timer bar do the opposite
	Because movement relates to top corner
	So shrinking timer bar reveals more of the base rect
	*/
	sf::Time time = clock1.getElapsedTime();
	if ((shooting1)&&(time.asSeconds() < attack1_time)){ 
		// in shooting mode, time to shoot decreases, decreasing red bar, colored sprite
		float height = boxsize * time.asSeconds() / attack1_time;
		timer_rect.setSize(sf::Vector2f(boxsize,height));
		base_rect.setFillColor(sf::Color(219, 88, 88)); // red
		timer_rect.setFillColor(sf::Color(192,192,192)); // grey
	}
	else if ((shooting1)&&(time.asSeconds() >= attack1_time)){ 
		// we cannot shoot and must change to regeneration
		shooting1 = false;
		regenerating1 = true;
		clock1.restart();
		attack_1_sprite.setTexture(attack_1_texture_bw);
	}
	else if ((regenerating1)&&(time.asSeconds() < regeneration1_time)){ 
		// regenerating SA1, blue bar grows, sprite b&w
		float height = boxsize - (boxsize * time.asSeconds() /regeneration1_time);
		timer_rect.setSize(sf::Vector2f(boxsize,height));
		base_rect.setFillColor(sf::Color(114, 228, 110)); // green
		timer_rect.setFillColor(sf::Color(192,192,192)); // grey
	
	}
	else if ((regenerating1)&&(time.asSeconds()>= regeneration1_time)){ // we have regenerated, now available again
		regenerating1 = false;
		initial_state();
	}
}

void Special_Attacks_Bar::draw(sf::RenderWindow& target){
	// Special Attack 1
	target.draw(base_rect);
	target.draw(timer_rect);
	target.draw(attack_1_sprite);
	target.draw(key1);
}

void Special_Attacks_Bar::draw(sf::RenderTexture& texture){
	texture.draw(base_rect);
	texture.draw(timer_rect);
	texture.draw(attack_1_sprite);
	texture.draw(key1);
}
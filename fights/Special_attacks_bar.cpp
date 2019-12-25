
#include "Special_Attacks_bar.h"

Special_Attacks_Bar::Special_Attacks_Bar() {
	attack1_available = true;
	attack1_time = 5; // We initialise how long these take - arbitrary
	regeneration1_time = 12;
	shooting1 = false;
	shooting2 = false;
	shooting3 = false;
	regenerating1 = false;

}

void Special_Attacks_Bar::initialise(){

    // Load images into our sprites
	if (!key1_texture.loadFromFile("Images/Special_Attacks_Bar/key1.png")) { std::cout << "could not load key1" << std::endl; }

	if (type == 10){ // type earth
		if (!attack_1_texture_bw.loadFromFile("Images/Special_Attacks_Bar/rock_bw.png")) { std::cout << "could not load rock bw" << std::endl;}; 
		attack_1_texture_bw.loadFromFile("Images/Special_Attacks_Bar/rock_bw.png");
		if (!attack_1_texture.loadFromFile("Images/Special_Attacks_Bar/rock.png")) { std::cout << "could not load rock" << std::endl;} 
		attack_1_texture.loadFromFile("Images/Special_Attacks_Bar/rock.png");
	};
	if (type == 20){ // type water
		if (!attack_1_texture_bw.loadFromFile("Images/Special_Attacks_Bar/water_bw.png")) { std::cout << "could not load water bw" << std::endl;}; 
		attack_1_texture_bw.loadFromFile("Images/Special_Attacks_Bar/water_bw.png");
		if (!attack_1_texture.loadFromFile("Images/Special_Attacks_Bar/water.png")) { std::cout << "could not load water" << std::endl;}; 
		attack_1_texture.loadFromFile("Images/Special_Attacks_Bar/water.png");
	};
	if (type == 30){ // type air
		if (!attack_1_texture_bw.loadFromFile("Images/Special_Attacks_Bar/air_bw.png")) { std::cout << "could not load air bw" << std::endl;}; 
		attack_1_texture_bw.loadFromFile("Images/Special_Attacks_Bar/air_bw.png");
		if (!attack_1_texture.loadFromFile("Images/Special_Attacks_Bar/air.png")) { std::cout << "could not load air" << std::endl;}; 
		attack_1_texture.loadFromFile("Images/Special_Attacks_Bar/air.png");
	};
	if (type == 40){ // type fire
		if (!attack_1_texture_bw.loadFromFile("Images/Special_Attacks_Bar/fire_bw.png")) { std::cout << "could not load fire bw" << std::endl;}; 
		attack_1_texture_bw.loadFromFile("Images/Special_Attacks_Bar/fire_bw.png");
		if (!attack_1_texture.loadFromFile("Images/Special_Attacks_Bar/fire.png")) { std::cout << "could not load fire" << std::endl;}; 
		attack_1_texture.loadFromFile("Images/Special_Attacks_Bar/fire.png");
	};

    // Set textures
	key1.setTexture(key1_texture);
	key1.setScale(2,2); // NB MUST SET SCALE ACCORDING TO WINDOW SIZE
	attack_1_sprite.setTexture(attack_1_texture);
	attack_1_sprite.setScale(sf::Vector2f(1, 1)); // NB MUST SET SCALE ACCORDING TO WINDOW SIZE
														// NB MUST BE CAREFUL W THE DIFFERENT SPRITES
	
	// Set up rectangles
	boxsize = 90; // NB CHANGE ACCORDING TO WINDOW SIZE
    base_rect.setFillColor(sf::Color(191,191,191)); // grey
    base_rect.setOutlineThickness(5);
    base_rect.setOutlineColor(sf::Color::Black);
    base_rect.setSize(sf::Vector2f(boxsize,boxsize));
    timer_rect.setFillColor(sf::Color(171, 227, 255)); // blueish: you can use this reddish: (230, 87, 87)
    timer_rect.setSize(sf::Vector2f(boxsize,boxsize));

	// Change origins
	attack_1_sprite.setOrigin(sf::Vector2f(attack_1_sprite.getGlobalBounds().width / 2, attack_1_sprite.getGlobalBounds().height / 2));
	key1.setOrigin(sf::Vector2f(key1.getGlobalBounds().width / 2, key1.getGlobalBounds().height / 2));

	// Set position - ACCORDING TO WINDOW SIZE
	xpos = 100;
	ypos = 550;
	setPosition(xpos, ypos);//might change it 
}

void Special_Attacks_Bar::setPosition(float x, float y) {
	base_rect.setPosition(x, y);
	timer_rect.setPosition(x, y);
	attack_1_sprite.setPosition(x + base_rect.getGlobalBounds().width / 2, y + base_rect.getGlobalBounds().height / 2);
	
	// Set the key to be centered at the top right of the base rectangle
	key1.setPosition(base_rect.getPosition().x , base_rect.getPosition().y );
	key1.move(sf::Vector2f(key1.getGlobalBounds().width / 2, key1.getGlobalBounds().height / 2));
}

void Special_Attacks_Bar::initial_state(){
	base_rect.setFillColor(sf::Color(191,191,191)); 	// grey
    base_rect.setSize(sf::Vector2f(boxsize,boxsize));
    timer_rect.setFillColor(sf::Color(171, 227, 255)); 	// blueis
    timer_rect.setSize(sf::Vector2f(boxsize,boxsize));
	attack1_available = true;
}

void Special_Attacks_Bar::update(sf::Time& time1, sf::Time& time2, sf::Time& time3, sf::Clock& clock1, sf::Clock& clock2, sf::Clock& clock3) {
	//std::cout<<time1.asSeconds()<<std::endl;
	// std::cout<<regenerating1<< " < R, S >" << shooting1 << std::endl;
	if ((regenerating1)&&(time1.asSeconds()>= regeneration1_time)){ // we have regenerated
		// std::cout<<"Regenerating"<<std::endl;
		regenerating1 = false;
		initial_state();
	}
	else if ((regenerating1)&&(time1.asSeconds() < regeneration1_time)){
		// std::cout<<"Finished Regenerating"<<std::endl;
		float height = boxsize * time1.asSeconds() /regenerating1;
		timer_rect.setSize(sf::Vector2f(boxsize,height));
		timer_rect.setFillColor(sf::Color(171, 227, 255));
		attack_1_sprite.setTexture(attack_1_texture_bw);
		// we are regenerating
		// blue bar must grow
		// sprite b&w
	}
	else if ((shooting1)&&(time1.asSeconds() < attack1_time)){
		// std::cout<<"Shooting and my time is ok"<<std::endl;
		float height = boxsize - (boxsize * time1.asSeconds() /regenerating1);
		timer_rect.setSize(sf::Vector2f(boxsize,height));
		timer_rect.setFillColor(sf::Color(219, 88, 88));
		attack_1_sprite.setTexture(attack_1_texture_bw);
		// we are attacking
		// sprite in color
		// red bar must decrease (function of 1-time1) : reddish : (230, 87, 87)
	}
	else if ((shooting1)&&(time1.asSeconds() >= attack1_time)){
		// we cannot shoot and must change to regeneration
		// std::cout<<"Shooting and my time is run out"<<std::endl;
		shooting1 = false;
		regenerating1 = true;
		clock1.restart();
		// set picture to b&w
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
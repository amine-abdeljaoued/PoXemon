#include "Artillery.h"
#include <random>
#include <list>

Artillery::Artillery(){
    max_available_bullets = 20;
    available_bullets = max_available_bullets;  // STart with all bullets available
    was_released = true;                        // Start being able to shoot
    attack_type = 0;                            // Start with standard attack
}

Artillery::~Artillery(){
    for (unsigned i = 0; i < bullets.size(); i++) {
        //delete bullets[i];
		//this is causing some exceptions so i remove it for now
    }
}

void Artillery::initialise(){
    attacksbar.initialise();
    std::cout<<attack_type<<" "<<type<<std::endl;
}

void Artillery::draw(sf::RenderWindow& target)  {
    for (unsigned i = 0; i < bullets.size(); i++) {
        target.draw((*bullets[i]).bullet);
	} 
}

void Artillery::draw(sf::RenderTexture& texture) {
    for (unsigned i = 0; i < bullets.size(); i++) {
        texture.draw((*bullets[i]).bullet);
	} 
}

void Artillery::new_click(float& x, float& y, const sf::FloatRect& bounds, sf::RenderWindow& window, const sf::Vector2i& mouse){
    if (attack_type == 0){
        new_shot(x,y,bounds, window, mouse);
    }
    else if (attack_type == 1){
        new_shot_special_attack1(x,y,bounds, window, mouse);
    }
}

void Artillery::new_shot(float& x, float& y, const sf::FloatRect& bounds, sf::RenderWindow& window, const sf::Vector2i& mouse){ 
    // takes bounds of sprite to know from where to shoot
    // takes our window
    // takes the clicked mouse position
    if (was_released && available_bullets > 0) {
        Bullet* new_bullet = new Bullet;
        sf::Vector2f initial_pos(x, y);
        (*new_bullet).setPosition(initial_pos); 

        //sf::Mouse::getPosition returns the position of the curson in window coordinates 
        //while all the entities use world coordinates.
        //We fix this by using the mapPixelToCoords member function.
        sf::Vector2f mouse_position = window.mapPixelToCoords(mouse);
        (*new_bullet).set_shoot_dir(mouse_position, initial_pos);

        bullets.push_back(new_bullet);//append the new bullet to our array

        available_bullets -= 1;
		bulletbar.update(-1);

        //std::cout << "available bullets -1 : " << available_bullets<<std::endl;
    }

    was_released = false;
}

void Artillery::new_shot_special_attack1(float& x, float& y, const sf::FloatRect& bounds, sf::RenderWindow& window, const sf::Vector2i& mouse){ 
    if (was_released && available_bullets > 0) {
        Bullet_Attack1* new_bullet = new Bullet_Attack1(type); // MUST BE GENERALISED TO TYPE
        sf::Vector2f initial_pos(x, y);
        (*new_bullet).setPosition(initial_pos); 

        sf::Vector2f mouse_position = window.mapPixelToCoords(mouse);
        (*new_bullet).set_shoot_dir(mouse_position, initial_pos);

        bullets.push_back(new_bullet);

        available_bullets -= 1;
		bulletbar.update(-1);
    }
    was_released = false;
}

void Artillery::new_shot_opp(float& x, float& y, const sf::FloatRect& bounds, sf::RenderWindow& window, float& xshoot, float& yshoot){
    if (was_released && available_bullets > 0) {
        if (rand() < 0.08 * ((double)RAND_MAX + 1.0)) { // probability of shooting of 8% at each update -- can change depending on level?
            Bullet* new_bullet = new Bullet;
            sf::Vector2f initial_pos(x, y);
            (*new_bullet).setPosition(initial_pos); 

            sf::Vector2f direction(xshoot, yshoot);
            sf::Vector2f current(x,y);
        
            (*new_bullet).set_shoot_dir(direction, current);
            bullets.push_back(new_bullet);  // append the new bullet to our array
            available_bullets -= 1;
        }
    }
}

int Artillery::update(sf::RenderWindow& window, float& deltaTime, sf::Clock& clock, sf::Time& elapsed, sf::Time& attack1, 
                sf::Time& attack2, sf::Time& attack3, sf::Clock& clock1, sf::Clock& clock2, sf::Clock& clock3, 
                const sf::Sprite & opponent_sprite, float& groundY){
	int res = 0;
    // update which type of attack we are in: other atttacks to be implemented
    // Press 1 and can access SA1
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))&&(attacksbar.attack1_available)){
        attack_type = 1;
        attacksbar.attack1_available = false;
        attacksbar.shooting1 = true;
        clock1.restart();
    }
    // If we're not shooting in any of the special attacks we must be in normal attack
    if ((!attacksbar.shooting1)&&(attacksbar.shooting2)&&(attacksbar.shooting3)){
        attack_type = 0;
    }

	std::list<int> to_delete;//indices of the bullets to delete
	//we will erase bullets after the loop (since otherwise we would modify the vector bullets)

    for (int  i = 0; i < bullets.size(); i++) {
        //Check if the bullets are offscreen
        if ((*(bullets[i])).offscreen(window)){
			to_delete.push_back(i);
        }
		// Collisions with the opponenent
        // PROBLEM HERE: with special attack 1 bullets sometimes this doesn't work .... 
		if (Collision::PixelPerfectTest((*(bullets[i])).bullet, opponent_sprite)) {
            bool b = (typeid(*(bullets[i])) == typeid(Bullet_Attack1)); // Bool to check what typeof bullet (special attack 1 or normal)
            
            if ( (b) && (!((*(bullets[i])).deleting))) {res = 10;}      // Enemy of the pokemon shooting thes bullets will get -X health 
            else if (!b) {res = 3;}
            if (!((*(bullets[i])).deleting)) {(*(bullets[i])).deletion();}
		}
        // Update individual bullets
        (*(bullets[i])).update(deltaTime, groundY);
        // Bullet completed its deleting process
        if ((*(bullets[i])).deleted){
			to_delete.push_back(i);
        }
    }
    // Update the special attacks bar
    attacksbar.update(attack1, attack2, attack3, clock1, clock2, clock3);

	//delete offscreen or collided bullets
	for (auto it = to_delete.cbegin(); it != to_delete.cend(); it++) {
		bullets.erase(bullets.begin() + *it);
		//delete bullets[*it];
	}


	//regenerate bullets every 1 second
    if (elapsed.asSeconds() > 1.0f && available_bullets < max_available_bullets) {
			available_bullets += 1;
			bulletbar.update(1);
			clock.restart();
	}
	return res;
}


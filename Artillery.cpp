#include "Artillery.h"

Artillery::Artillery(){
    max_available_bullets = 20;
    available_bullets = max_available_bullets;  // STart with all bullets available
    was_released = true;                        // Start being able to shoot
}

void Artillery::draw(sf::RenderTarget& target) const {
    for (unsigned i = 0; i < bullets.size(); i++) {
        target.draw(bullets[i].bullet);
	}
}

void Artillery::new_shot(float& x, float& y, const sf::FloatRect& bounds, sf::RenderTarget& window, const sf::Vector2i& mouse){ 
    // takes bounds of sprite to know from where to shoot
    // takes our window
    // takes the clicked mouse position
    if (was_released && available_bullets > 0) {
        Bullet new_bullet;
        //we want the bullet to start from the midlle right of the pokemon
        //for later: careful if we change the origin of the pokemon
        float x_bullet = x + bounds.width / 2;
        float y_bullet = y + bounds.height / 2;
        sf::Vector2f initial_pos(x_bullet, y_bullet);
        new_bullet.setPosition(initial_pos); // start at the 'middle-right' of the pokemon
        //that stuff should go in the bullet class

        //sf::Mouse::getPosition returns the position of the curson in window coordinates 
        //while all the entities use world coordinates.
        //We fix this by using the mapPixelToCoords member function.
        sf::Vector2f mouse_position = window.mapPixelToCoords(mouse);
        new_bullet.set_shoot_dir(mouse_position, initial_pos);

        bullets.push_back(new_bullet);//append the new bullet to our array

        available_bullets -= 1;
		bulletbar.update(-1);

        std::cout << "available bullets -1 : " << available_bullets<<std::endl;
    }

    was_released = false;
}

void Artillery::new_shot_opp(float& x, float& y, const sf::FloatRect& bounds, sf::RenderTarget& window, float& xshoot, float& yshoot){
    if (was_released && available_bullets > 0) {
        Bullet new_bullet;
        float x_bullet = x + bounds.width / 2;
        float y_bullet = y + bounds.height / 2;
        sf::Vector2f initial_pos(x_bullet, y_bullet);
        new_bullet.setPosition(initial_pos); 

        sf::Vector2f direction(xshoot, yshoot);
        sf::Vector2f current(x,y);
    
        new_bullet.set_shoot_dir(direction, current);
        bullets.push_back(new_bullet);//append the new bullet to our array
        available_bullets -= 1;
    }
}

void Artillery::update(float& deltaTime, sf::Clock& clock, sf::Time& elapsed){
    for (int  i = 0; i < bullets.size(); i++) {
        bullets[i].update(deltaTime);
        if (bullets[i].offscreen())
            bullets.erase(bullets.begin() + i);
        //we loop over the bullets and if a bullet is offscreen, remove it
        //we will also need to chack collisions
        // I think the 'erase()' this is pretty inefficient, we might need to find a better way
    }

	//regenerate bullets every 1 second
    if (elapsed.asSeconds() > 1.0f && available_bullets < max_available_bullets) {
			available_bullets += 1;
			bulletbar.update(1);
			clock.restart();
	}

}
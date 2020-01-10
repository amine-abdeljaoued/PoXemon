#include "Bullet.h"

Bullet::Bullet() {
	deleted = false;
	deleting = false;
	if (!bpic.loadFromFile("fights/Images/red_bullet.png")) std::cout << "could not load bullet image" << std::endl;
	bpic.loadFromFile("fights/Images/red_bullet.png");//to change
	bullet.setTexture(bpic);
	//I find easier to set the origin at center
	bullet.setOrigin(sf::Vector2f(bullet.getLocalBounds().width / 2, bullet.getLocalBounds().height / 2));
	bullet.setScale(sf::Vector2f(0.05f, 0.05f));
}

void Bullet::deletion(){
	deleted = true;
}

void Bullet::setPosition(sf::Vector2f& pos) {
	//x = xpos;
	//y = ypos;
	position = pos;
	bullet.setPosition(position);
}


void Bullet::set_shoot_dir(const sf::Vector2f& mouse_position, const sf::Vector2f& initial_pos) {
	//float x and float y stand for the initial position
	shoot_dir = mouse_position - initial_pos;
	//now we normalize this vector
	float norm = sqrt(pow(shoot_dir.x, 2) + pow(shoot_dir.y, 2));
	shoot_dir = shoot_dir / norm;
}

bool Bullet::update(float& deltaTime, float& groundY) {
	//x += shoot_dir.x * deltaTime *max_speed;
	//y += shoot_dir.y * deltaTime *max_speed;
	reflect_ground(groundY);
	bullet.setTexture(bpic);
	position += shoot_dir *deltaTime* max_speed;
	setPosition(position);
	return true;
}

bool Bullet::offscreen(sf::RenderWindow& window) {
	sf::Vector2f window_bounds = window.mapPixelToCoords(static_cast<sf::Vector2i>(window.getSize()));
	if (position.x<-20 || position.x >window_bounds.x+20 ||  position.y<-20 || position.y >window_bounds.y+20) {
		std::cout << "offscreen !" << std::endl;
		return true;
	}
	return false;
}

void Bullet::reflect_ground(float& groundY) {
	if (bullet.getPosition().y > groundY + 70){
		shoot_dir.y = -abs(shoot_dir.y); // make it 'bounce' on the ground
		}
}

//---------------------------------------------------------------------------------------------------
// SPECIAL ATTACK 1

void Bullet_Attack1::update_image(){
	if (!deleting){
		if((posx < array[4]) && (posy <= array[5]-1)){			//Case 1:  not in the last line, not last element of row
			posx++;
		}
		else if((posx == array[4]) && (posy <= array[5]-1)){	//Case 2: not in the last line, last element of row
			posx = 0;
			posy ++;
		}
		else if((posx < array[6]) && (posy == array[5])){		//Case 3: last line, not last element of row
			posx ++;
		}
		else if((posx == array[6]) && (posy == array[5])){		//Case 4: last line, last element of row
			posx = 0;
			posy = 0;
		}
		bullet.setTexture(bpic);
		bullet.setTextureRect(sf::IntRect(posx*(array[2]), posy*(array[3]), array[2], array[3]));
	}
	else{
		if((posx < array[12]) && (posy <= array[13]-1)){		//Case 1:  not in the last line, not last element of row
			posx++;
		}
		else if((posx == array[12]) && (posy <= array[13]-1)){	//Case 2: not in the last line, last element of row
			posx = 0;
			posy ++;
		}
		else if((posx < array[14]) && (posy == array[13])){		//Case 3: last line, not last element of row
			posx ++;
		}
		else if((posx == array[14]) && (posy == array[13])){	//Case 4: last line, last element of row
			deleted = true;
		}

		bullet.setTexture(deleting_pic);
		bullet.setTextureRect(sf::IntRect(array[8]+posx*(array[10]),array[9]+posy*(array[11]),array[10],array[11]));
		bullet.setScale(sf::Vector2f(array[15], array[15]));
	}
}

bool Bullet_Attack1::update(float& deltaTime, float& groundY){
	if (i<3){i++;}
	if (i >= 3){
		i = 1;
		update_image();
	}
	reflect_ground(groundY);
	if (!deleting){
		position += shoot_dir * deltaTime * max_speed;
		setPosition(position);
		return true;
	}
}

void Bullet_Attack1::deletion(){
	deleting = true;
	bullet.setTexture(deleting_pic);
	bullet.setTextureRect(sf::IntRect(array[8]*array[10],array[9]*array[11],array[10],array[11]));
	bullet.setScale(sf::Vector2f(array[15], array[15]));
	posx = array[8];
	posy = array[9];
}

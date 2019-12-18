#include "Player.h"

template <typename T>
//will be used for either player or opponent

void fall(T& eevee, float& groundY, float& deltaTime) {//make player fall if it is still in the air
	if (eevee.y < groundY) {

		eevee.velocityY += 981.0f * deltaTime;
		eevee.y += eevee.velocityY * deltaTime;
		eevee.sprite.setPosition(eevee.x, eevee.y);

		if (eevee.y >= groundY) {
			eevee.y = groundY;
			eevee.velocityY = 0.0f;
		}

	}
}

void initialize_state_5_6(char game_mode, Pokemon poke, sf::Font font, sf::Text& text_fainted, sf::Text& choose_pokemon, sf::Text& leave_fight, sf::RenderTarget& target, Pokemon_Button* buttons[], sf::Sprite& running_sprite) {

	//the menu is almost the same when we play against a wild pokemon or a trainer
	//the difference is that we cannot escape against a trainer 
	//hence in 't' mode there is no run button and pokemon buttons are placed at the center

	if (poke.health.health <= 0) {
		text_fainted.setString(poke.name + " fainted!");
	}else{
		text_fainted.setString(poke.enemy->name + " fainted!");
	}

	//text elements
	choose_pokemon.setFont(font);
	text_fainted.setFont(font);
	choose_pokemon.setCharacterSize(30);
	text_fainted.setCharacterSize(50);
	choose_pokemon.setFillColor(sf::Color::Black);
	text_fainted.setFillColor(sf::Color::Black);
	leave_fight.setFillColor(sf::Color::Black);
	text_fainted.setOrigin(text_fainted.getGlobalBounds().width / 2, text_fainted.getGlobalBounds().height / 2);
	choose_pokemon.setOrigin(choose_pokemon.getGlobalBounds().width / 2, choose_pokemon.getGlobalBounds().height/2);
	
	if (game_mode == 'w') {
		leave_fight.setFont(font);
		leave_fight.setCharacterSize(30);
		leave_fight.setOrigin(leave_fight.getGlobalBounds().width / 2, leave_fight.getGlobalBounds().height / 2);
	}
	
	//set their positions.
	int placement = 3;
	if (game_mode == 't') placement = 2;

	choose_pokemon.setPosition(target.getSize().x / placement, target.getSize().y /4);
	text_fainted.setPosition(target.getSize().x / 2, target.getSize().y / 9);
	leave_fight.setPosition(target.getSize().x *2/3, target.getSize().y / 4);

	//set position of the buttons
	buttons[0]->setPosition(target.getSize().x / placement, target.getSize().y * 7/16 );
	buttons[1]->setPosition(target.getSize().x / placement, target.getSize().y * 9/16 );
	buttons[2]->setPosition(target.getSize().x / placement, target.getSize().y * 11/16 );

	//update life of the pokemon on its button
	buttons[poke.index]->setHealth(poke.health.health);

}

void const draw_state_5_6(char game_mode,  sf::Font& font, sf::Text& text_fainted, sf::Text choose_pokemon, sf::Text leave_fight, sf::RenderTarget& target, Pokemon_Button* buttons[], sf::Sprite& running_sprite) {
	//text elements
	choose_pokemon.setFont(font);//for some reason I need to reset the font here otherwise it throws some exceptions I am not able to fix
	text_fainted.setFont(font);
	target.draw(text_fainted);
	target.draw(choose_pokemon);
	

	//buttons
	buttons[0]->draw(target);
	buttons[1]->draw(target);
	buttons[2]->draw(target);


	if (game_mode == 'w') { 
		leave_fight.setFont(font);
		target.draw(leave_fight);
		target.draw(running_sprite);
	}
	
}

void update_state_5_6(char game_mode, sf::RenderWindow& window, Pokemon_Button* buttons[], int& clicked_button, sf::Sprite& running_sprite ) { //this function will change the clicked_button value if a button is clicked

	if ((sf::Event::MouseMoved) || (sf::Event::MouseButtonPressed)) {
		sf::Vector2i mousepixel = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_pos = window.mapPixelToCoords(mousepixel);

	//check for clicked pokemon buttons
		for (int i = 0; i < 3; i++) {
			(*buttons[i]).update_mouse(mouse_pos, clicked_button);
		}

		if (game_mode == 'w') {
			//check for clicked run button
			//would be nice to make it 'pixel perfect'
			if (running_sprite.getGlobalBounds().contains(mouse_pos)) {
				running_sprite.setScale(2.2, 2.2); // slightly bigger when the mouse is on the button
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					std::cout << "you pressed the run button" << std::endl;
					clicked_button = -1;
				}
			}
			else {
				running_sprite.setScale(2, 2);
			}
		}
	}

}

void initialize_state7(bool won, sf::Text& lost_fight, sf::Font& font, sf::RenderWindow& window) {

	if (won) {
		lost_fight.setString("You won the duel!");
	}
	else {
		lost_fight.setString("You lost the duel!");
	}
	lost_fight.setFont(font);
	lost_fight.setCharacterSize(60);
	lost_fight.setFillColor(sf::Color::Black);
	lost_fight.setOrigin(lost_fight.getGlobalBounds().width/2, lost_fight.getGlobalBounds().height );
	lost_fight.setPosition(window.getSize().x /2, window.getSize().y / 2);
}



void initialize_state_8(Pokemon& poke, sf::Font& font, sf::Text& text_fainted, sf::RenderWindow& window) {
	
	text_fainted.setString(poke.name + " fainted!");
	text_fainted.setFont(font);
	text_fainted.setCharacterSize(50);
	text_fainted.setFillColor(sf::Color::Black);
	text_fainted.setOrigin(text_fainted.getGlobalBounds().width / 2, text_fainted.getGlobalBounds().height / 2);
	text_fainted.setPosition(window.getSize().x / 2, window.getSize().y / 9);

	//maybe add a button to leave ?
	
}










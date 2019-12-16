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

//sould be different in function of some parameters
//no more alive pokemons in our backpack -> leave the fight and go back to the city directly
//against a trainer -> not possible to leave the fight
void initialize_state_5(Pokemon poke, sf::Font font, sf::Text& you_fainted, sf::Text& choose_pokemon, sf::Text& leave_fight, sf::RenderTarget& target, Pokemon_Button* buttons[], sf::Sprite& running_sprite) {

	you_fainted.setString(poke.name + " fainted!");
	//text elements
	choose_pokemon.setFont(font);
	you_fainted.setFont(font);
	leave_fight.setFont(font);
	choose_pokemon.setCharacterSize(30);
	you_fainted.setCharacterSize(50);
	leave_fight.setCharacterSize(30);
	choose_pokemon.setFillColor(sf::Color::Black);
	you_fainted.setFillColor(sf::Color::Black);
	leave_fight.setFillColor(sf::Color::Black);

	you_fainted.setOrigin(you_fainted.getGlobalBounds().width / 2, you_fainted.getGlobalBounds().height / 2);
	choose_pokemon.setOrigin(choose_pokemon.getGlobalBounds().width / 2, choose_pokemon.getGlobalBounds().height/2);
	leave_fight.setOrigin(leave_fight.getGlobalBounds().width / 2, leave_fight.getGlobalBounds().height/2);
	
	//set their positions
	choose_pokemon.setPosition(target.getSize().x / 3, target.getSize().y /4);
	you_fainted.setPosition(target.getSize().x / 2, target.getSize().y / 9);
	leave_fight.setPosition(target.getSize().x *2/3, target.getSize().y / 4);

	//set position of the buttons
	buttons[0]->setPosition(target.getSize().x / 3, target.getSize().y * 7/16 );
	buttons[1]->setPosition(target.getSize().x / 3, target.getSize().y * 9/16 );
	buttons[2]->setPosition(target.getSize().x / 3, target.getSize().y * 11/16 );
	//update life of the dead pokemon on its button
	int i = 0;

	buttons[poke.index]->setHealth(i);//when our pokemons dies, set its health (on its button) to 0

	//running sprite




}

void const draw_state_5(sf::Font& font, sf::Text& you_fainted, sf::Text choose_pokemon, sf::Text leave_fight, sf::RenderTarget& target, Pokemon_Button* buttons[], sf::Sprite& running_sprite) {
	//text elements
	choose_pokemon.setFont(font);//for some reason I need to reset the font here otherwise it throws some exceptions I am not able to fix
	you_fainted.setFont(font);
	leave_fight.setFont(font);
	target.draw(you_fainted);
	target.draw(choose_pokemon);
	target.draw(leave_fight);

	//buttons
	buttons[0]->draw(target);
	buttons[1]->draw(target);
	buttons[2]->draw(target);

	target.draw(running_sprite);
}

void update_state5(sf::RenderWindow& window, Pokemon_Button* buttons[], int& clicked_button, sf::Sprite& running_sprite ) { //this function will change the clicked_button value if a button is clicked
	// Know where the mouse is
	// Buttons go red when hovering

	if ((sf::Event::MouseMoved) || (sf::Event::MouseButtonPressed)) {
		sf::Vector2i mousepixel = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_pos = window.mapPixelToCoords(mousepixel);

	//check for clicked pokemon buttons
		for (int i = 0; i < 3; i++) {
			(*buttons[i]).update_mouse(mouse_pos, clicked_button);
		}

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








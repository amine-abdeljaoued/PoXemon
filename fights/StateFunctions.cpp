
#include "StateFunctions.h"

void StateFunctions1::initialise_background(sf::RenderWindow& window, std::string path, sf::Sprite& background, sf::Texture& texture){
	// Function that sets up our background to be the same size as the window
	// Need to initialise the sprite and texture of the background before though
	sf::Vector2u TextureSize;  //Added to store texture size.
	sf::Vector2u WindowSize;   //Added to store window size.

	if(!texture.loadFromFile(path)){std::cout<<"Background didn't load"<<std::endl;}
	else
	{
		TextureSize = texture.getSize(); 	//Get size of texture.
		WindowSize = window.getSize();      //Get size of window.

		float ScaleX = (float) WindowSize.x / TextureSize.x;
		float ScaleY = (float) WindowSize.y / TextureSize.y; //Calculate scale.

		background.setTexture(texture);
		background.setScale(ScaleX, ScaleY);	//Set scale.  
  	}
}

void StateFunctions1::initialise_buttons(sf::RectangleShape& start_button, sf::RectangleShape& info_button, sf::RenderWindow& window, sf::Font& font, sf::Text& start_text,
                            sf::Text& info_text, sf::Text& intro_text, sf::Sprite& opp, sf::Sprite& star, sf::Texture& star_texture){
	// Window size
	float x = window.getSize().x;
	float y = window.getSize().y;

    // Rectangles
    start_button.setFillColor(sf::Color::White);
    info_button.setFillColor(sf::Color::White);
    start_button.setOutlineThickness(4);
    info_button.setOutlineThickness(4);
    start_button.setOutlineColor(sf::Color::Black);
    info_button.setOutlineColor(sf::Color::Black);
    start_button.setSize(sf::Vector2f(x/5,y/5));
    info_button.setSize(sf::Vector2f(x/5,y/5));

    //Sprites
    if (!star_texture.loadFromFile("Images/12star.png")){ std::cout << "could not load" << std::endl;}
    star_texture.loadFromFile("Images/12star.png");
    star.setTexture(star_texture);
    star.setScale(sf::Vector2f(0.75, 0.75)); // How to make it relate to window size???
    opp.setScale(sf::Vector2f(1,1));
    opp.setOrigin(0,0);

    // Text 
    std::string start = "Start";
    std::string info = "How to Play";
    
	start_text.setFont(font);
    info_text.setFont(font);
    intro_text.setFont(font);
	start_text.setCharacterSize(30);
    info_text.setCharacterSize(30);
    intro_text.setCharacterSize(60);
    start_text.setFillColor(sf::Color::Black);
    info_text.setFillColor(sf::Color::Black);
    intro_text.setFillColor(sf::Color::Black); 
    start_text.setString(start);
    info_text.setString(info);

	// Setting origin at centre
	opp.setPosition(0,0); // we have to compensation for the initial position of the sprite
	intro_text.setOrigin(intro_text.getGlobalBounds().width/2, intro_text.getGlobalBounds().height/2);
	info_text.setOrigin(info_text.getGlobalBounds().width/2, info_text.getGlobalBounds().height/2);
	start_text.setOrigin(start_text.getGlobalBounds().width/2, start_text.getGlobalBounds().height/2);
	start_button.setOrigin(start_button.getGlobalBounds().width/2, start_button.getGlobalBounds().height/2);
	info_button.setOrigin(info_button.getGlobalBounds().width/2, info_button.getGlobalBounds().height/2);
	star.setOrigin(star.getLocalBounds().width/2, star.getLocalBounds().height/2);
	opp.setOrigin(opp.getLocalBounds().width/2, opp.getLocalBounds().height/2);

	// setting the position
	float xoffset = 3*x/25;
	float yoffset1 = y/15;
	float yoffset2 = y/5;
	float yoffset3 = y/15;

	intro_text.move(x/2, y/7);
	start_text.move(x/2 - xoffset, y/2 - yoffset1);
	start_button.move(x/2 - xoffset, y/2 - yoffset1);
	info_text.move(x/2 - xoffset, y/2 + yoffset2);
	info_button.move(x/2 - xoffset, y/2 + yoffset2);
	star.move(x/2 + xoffset, y/2 + yoffset3);
	opp.move(x/2 + xoffset, y/2 + yoffset3);
}

void StateFunctions1::draw1(sf::RenderWindow& window, sf::RectangleShape& shape1, sf::RectangleShape& shape2, sf::Text& text1, sf::Text& text2,
    		sf::Text& text3, sf::Sprite& sprite, sf::Sprite& bg ){
	window.draw(shape1);
	window.draw(shape2);
	window.draw(text1);
	window.draw(text2);
	window.draw(text3);
	window.draw(bg);
	window.draw(sprite);
}

void StateFunctions1::draw_blurry_background(sf::RenderWindow& window, sf::Sprite& background, sf::RectangleShape box, Backpack& bag, Player& player, 
			Opponent& opponent, sf::Shader* shader){
	window.draw(background, shader); // draw objects of the fight with a blur
	bag.draw(window, shader);
	player.draw(window, shader);
	opponent.draw(window, shader);
	window.draw(box);
}

int StateFunctions1::update_state1(sf::RenderWindow& window, sf::RectangleShape& start_button, sf::RectangleShape& info_button, sf::Sprite& star, sf::Clock& clock){
    //Rotate star
    star.rotate(2); 
    // Buttons go red when hovering
    if ((sf::Event::MouseMoved)||(sf::Event::MouseButtonPressed)){
        sf::Vector2i mousepixel = sf::Mouse::getPosition(window);
        sf::Vector2f mouse_pos = window.mapPixelToCoords(mousepixel);

        if (start_button.getGlobalBounds().contains(mouse_pos)){
            start_button.setFillColor(sf::Color(255,99,99)); //reddish
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				clock.restart();
                return 10; 
				// should change to choose pokemon
				// then to countdown
				// when the countdown is done we return 2
            }
        }
        else {
            start_button.setFillColor(sf::Color::White);
        }
		if (info_button.getGlobalBounds().contains(mouse_pos)){
			info_button.setFillColor(sf::Color(255,99,99));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				clock.restart();
				return 10;
				// different state entirely...
			}
		}
		else {
			info_button.setFillColor(sf::Color::White);
		}
		return 1;
    }
}

void StateFunctions1::initialise_countdown(sf::RenderTarget& window){
	text.setString("3");
    text.setCharacterSize(max_char_size);
    font.loadFromFile("upheavtt.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height);
    text.move(window.getSize().x/2 , 2*window.getSize().y/5);
    bool draw_count = true;
}

void StateFunctions1::shrink_text(sf::Text& text, float deltatime){
	float add_font_size = 5 * deltatime * max_char_size / 2 ; // must be in proportion to how long its on the screen for
                                                                // i.e. we're on screen for 4/10 = 2/5 of a second
    int font_size = (int)text.getCharacterSize() - (int)add_font_size ;
    text.setCharacterSize(font_size);
}

int StateFunctions1::countdown(sf::RenderWindow& window, float deltatime, sf::Time time){
	 /*  Idea: 
            Number shows large for 0.5s
            Number shrinks for 0.4s
            Not shown for 0.1s (smoother looking)
            After 4s enter game mode
        */
        if ((0.5 < time.asSeconds())&&(time.asSeconds() <= 0.9)){
            shrink_text(text, deltatime);
        }
        else if ((0.9 < time.asSeconds())&&(time.asSeconds() <= 1)){
            draw_count = false;
        }
        else if ((time.asSeconds()>1)&&(time.asSeconds()<=1.5)){
            draw_count = true;
            text.setCharacterSize(max_char_size);
            text.setString("2");
        }
        else if ((time.asSeconds()>1.5) && (time.asSeconds()<1.9)){
            shrink_text(text, deltatime);
        }
        else if ((1.9 < time.asSeconds())&&(time.asSeconds() <= 2)){
            draw_count = false;
        }
        else if ((time.asSeconds()>2)&&(time.asSeconds()<=2.5)){
            draw_count = true;
            text.setCharacterSize(max_char_size);
            text.setString("1");
        }
        else if ((time.asSeconds()>2.5)&&(time.asSeconds()<=2.9)){
            shrink_text(text, deltatime);
        }
        else if ((2.9 < time.asSeconds())&&(time.asSeconds() <= 3)){
            draw_count = false;
        }
        else if ((time.asSeconds()>3)&&(time.asSeconds()<=4)){
            draw_count = true;
            text.setCharacterSize(max_char_size);
            text.setString("Go!");
        }
        else if (time.asSeconds()>4){
            return 2;
        }
		return 10;
}

//------------------------------------------------------------------------------------------------------------

#pragma once
#include "Player.h"

void StateFunctions56::fall(Pokemon& eevee, float& groundY, float& deltaTime) {//make player fall if it is still in the air
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

void StateFunctions56::initialize_state_5_6(char game_mode, Pokemon poke, sf::Font font, sf::Text& text_fainted, sf::Text& choose_pokemon, sf::Text& leave_fight, sf::RenderWindow& target, Pokemon_Button* buttons[], sf::Sprite& running_sprite) {

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

void const StateFunctions56::draw_state_5_6(char game_mode,  sf::Font& font, sf::Text& text_fainted, sf::Text choose_pokemon, sf::Text leave_fight, sf::RenderWindow& target, Pokemon_Button* buttons[], sf::Sprite& running_sprite) {
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

void StateFunctions56::update_state_5_6(char game_mode, sf::RenderWindow& window, Pokemon_Button* buttons[], int& clicked_button, sf::Sprite& running_sprite ) { //this function will change the clicked_button value if a button is clicked

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

void StateFunctions56::initialize_state7(bool won, sf::Text& lost_fight, sf::Font& font, sf::RenderWindow& window) {

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




void StateFunctions56::initialize_state_8(Pokemon& poke, sf::Font& font, sf::Text& text_fainted, sf::RenderWindow& window) {
	
	text_fainted.setString(poke.name + " fainted!");
	text_fainted.setFont(font);
	text_fainted.setCharacterSize(50);
	text_fainted.setFillColor(sf::Color::Black);
	text_fainted.setOrigin(text_fainted.getGlobalBounds().width / 2, text_fainted.getGlobalBounds().height / 2);
	text_fainted.setPosition(window.getSize().x / 2, window.getSize().y / 9);

	//maybe add a button to leave ?
	
}

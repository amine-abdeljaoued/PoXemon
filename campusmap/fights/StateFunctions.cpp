
#include "StateFunctions.h"

StateFunctions1::StateFunctions1(){/*do nothing*/}

//no need for opponent
void StateFunctions1::initialise(char& game_mode, Opponent& opponent, Player& player, sf::RenderWindow& window, sf::Font& font) {
	opp = opponent.sprite;

	if (game_mode == 'w') intro_text.setString("You encountered a wild pokemon!");
	if (game_mode == 't') intro_text.setString("You are in a duel! ");
    initialise_buttons(window, font);
	initialise_howto(window);
	initialise_countdown(window);
	opponent.health.update();
	player.health.update();
}

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

void StateFunctions1::initialise_howto(sf::RenderWindow& window){

	if(!how_texture.loadFromFile("fights/Images/howto.png")){std::cout<<"how to didn't load"<<std::endl;}
	if(!quit_texture.loadFromFile("fights/Images/quit.png")){std::cout<<"quit button didn't load"<<std::endl;}

	sf::Vector2u TextureSize = how_texture.getSize(); 	//Get size of texture.
	sf::Vector2u TextureSize1 = quit_texture.getSize();
	sf::Vector2u WindowSize = window.getSize();      //Get size of window.

	float ScaleY = (float) WindowSize.y / TextureSize.y; //Calculate scale.
	float Scale2 = (float) WindowSize.y / TextureSize1.y;

	how_to.setTexture(how_texture);
	quit.setTexture(quit_texture);
	how_to.setScale(5*ScaleY/6, 5*ScaleY/6);	//Set scale.
	quit.setScale(Scale2/10, Scale2/10);

	how_to.setOrigin(how_to.getLocalBounds().width/2, how_to.getLocalBounds().height/2);
	quit.setOrigin(quit.getLocalBounds().width/2, quit.getLocalBounds().height/2);
	how_to.setPosition(0, 0);
	quit.setPosition(0, 0);
	how_to.move(window.getSize().x/2, window.getSize().y/2);
	quit.move(window.getSize().x/2 + how_to.getGlobalBounds().width/2,
			window.getSize().y/2 - how_to.getGlobalBounds().height/2 + quit.getGlobalBounds().height/5);
}

void StateFunctions1::initialise_buttons(sf::RenderWindow& window, sf::Font& font){ // to rewrite 
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
    if (!star_texture.loadFromFile("fights/Images/12star.png")){ std::cout << "star could not load" << std::endl;}
    star_texture.loadFromFile("fights/Images/12star.png");
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


	// Reset position - must compensate for their initial position (can call fights multiple times)
	opp.setPosition(0,0);
	star.setPosition(0,0);
	intro_text.setPosition(0,0);
	info_text.setPosition(0,0);
	start_text.setPosition(0,0);
	info_button.setPosition(0,0);
	start_button.setPosition(0,0);

	// Setting origin at centre
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
	start_text.move(x/2 , y/2 - yoffset1);
	start_button.move(x/2 , y/2 - yoffset1);
	info_text.move(x/2 , y/2 + yoffset2);
	info_button.move(x/2, y/2 + yoffset2);
	
	//star.move(x/2 + xoffset, y/2 + yoffset3);
	//opp.move(x/2 + xoffset, y/2 + yoffset3);
}

void StateFunctions1::draw1(sf::RenderWindow& window){
	window.draw(start_button);
	window.draw(info_button);
	window.draw(start_text);
	window.draw(info_text);
	window.draw(intro_text);
	//window.draw(star);
	//window.draw(opp);
}

void StateFunctions1::draw_blurry_background(sf::RenderWindow& window, sf::Sprite& background, Backpack& bag, Player& player,
			Opponent& opponent, sf::Shader* shader){
	// we create a new texture with all the objects on the screen
	sf::RenderTexture texture;
    texture.create(window.getSize().x, window.getSize().y);
    texture.clear();
    texture.draw(background);
    bag.draw(texture);
    player.draw(texture);
	opponent.draw(texture);
    texture.display();

	// turn the texture into a sprite which we draw with the shader
    sf::Sprite sprite(texture.getTexture());
    window.draw(sprite, shader);
}

void StateFunctions1::draw_how_to(sf::RenderWindow& window){
	window.draw(how_to);
	window.draw(quit);
}

//int StateFunctions1::update_state1(sf::RenderWindow& window, sf::Clock& clock){
//    //Rotate star
//    star.rotate(2);
//    // Buttons go red when hovering
//    if ((sf::Event::MouseMoved)||(sf::Event::MouseButtonPressed)){
//        sf::Vector2i mousepixel = sf::Mouse::getPosition(window);
//        sf::Vector2f mouse_pos = window.mapPixelToCoords(mousepixel);
//
//        if (start_button.getGlobalBounds().contains(mouse_pos)){
//            start_button.setFillColor(sf::Color(255,99,99)); //reddish
//            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
//				clock.restart();
//
//                return 21;
//				//go to the menu to change pokemon
//
//				// should change to choose pokemon
//				// then to countdown
//				// when the countdown is done we return 2
//            }
//        }
//        else {
//            start_button.setFillColor(sf::Color::White);
//        }
//		if (info_button.getGlobalBounds().contains(mouse_pos)){
//			info_button.setFillColor(sf::Color(255,99,99));
//			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
//				clock.restart();
//				return 15;
//				// should go to "how to play"
//			}
//		}
//		else {
//			info_button.setFillColor(sf::Color::White);
//		}
//		return 1;
//    }
//}

//state 1--------------------------------------------------------------------------------------------------------------
void StateFunctions1::initialize_state1(char& game_mode, sf::Sprite& opp_sprite,std::string& opp_n,int& opplvl, sf::RenderWindow& window, Pokemon_Button* buttons[], sf::Sprite& running_sprite, sf::Font& ffont) {
	initialise_howto(window);

	mode = game_mode;
	//text elements
	font = ffont;
	intro_text.setString("");
	if(game_mode == 'w') intro_text.setString("You encountered a wild pokemon!");
	if (game_mode == 't') intro_text.setString("You are in a duel! ");
	choose_pokemon.setString("");
	choose_pokemon.setString("choose your fighter");
	choose_pokemon.setFont(font);
	intro_text.setFont(font);
	choose_pokemon.setCharacterSize(20);
	intro_text.setCharacterSize(50);
	choose_pokemon.setFillColor(sf::Color::Black);
	intro_text.setFillColor(sf::Color::Black);
	choose_pokemon.setOrigin(choose_pokemon.getGlobalBounds().width / 2, choose_pokemon.getGlobalBounds().height / 2);
	choose_pokemon.setPosition(window.getSize().x / 3, window.getSize().y *5/16);
	intro_text.setOrigin(intro_text.getLocalBounds().width / 2, intro_text.getLocalBounds().height / 2);
	
	//choose_pokemon.setPosition(window.getSize().x / 3, window.getSize().y / 4);
	intro_text.setPosition(0, 0);
	intro_text.move(window.getSize().x / 2, window.getSize().y / 7);

	//how to play
	info_text.setString("");
	info_text.setString("How to play ?");
	info_text.setFont(font);
	info_text.setCharacterSize(25);
	info_text.setFillColor(sf::Color::Black);
	info_text.setPosition(0, 0);
	info_text.setOrigin(info_text.getGlobalBounds().width / 2, info_text.getGlobalBounds().height / 2);
	info_text.setPosition(window.getSize().x / 9, window.getSize().y / 20); //top left corner

	//pokemon buttons
	if (buttons[0]) buttons[0]->setPosition(window.getSize().x / 3, window.getSize().y * 7 / 16);
	if (buttons[1]) buttons[1]->setPosition(window.getSize().x / 3, window.getSize().y * 9 / 16);
	if (buttons[2]) buttons[2]->setPosition(window.getSize().x / 3, window.getSize().y * 11 / 16);

	//opponent + star
	opp.setTexture(*opp_sprite.getTexture());
	if (!star_texture.loadFromFile("fights/Images/12star.png")) { std::cout << "star could not load" << std::endl; }
	star_texture.loadFromFile("fights/Images/12star.png");
	star.setTexture(star_texture);
	star.setOrigin(star.getGlobalBounds().width / 2, star.getGlobalBounds().height / 2);
	star.setScale(sf::Vector2f(0.75, 0.75)); // How to make it relate to window size???
	opp.setScale(sf::Vector2f(1, 1));
	opp.setOrigin(opp.getGlobalBounds().width / 2, opp.getGlobalBounds().height / 2);
	star.setPosition(0, 0);
	star.move(window.getSize().x / 2 + 3 * window.getSize().x / 25, window.getSize().y / 2 + window.getSize().y / 15);
	opp.setPosition(0, 0);
	opp.move(window.getSize().x / 2 + 3 * window.getSize().x / 25, window.getSize().y / 2 + window.getSize().y / 15);
	//opponent name
	opp_name.setString("");
	std::string str = opp_n;
	opp_name.setString(str);
	opp_name.setFont(font);
	opp_name.setFillColor(sf::Color::Black);
	opp_name.setOrigin(opp_name.getGlobalBounds().width / 2, opp_name.getGlobalBounds().height / 2);
	opp_name.setCharacterSize(30);
	opp_name.setPosition(0, 0);
	opp_name.setPosition(window.getSize().x / 2 + 3 * window.getSize().x / 25, window.getSize().y / 2 + window.getSize().y / 15 - star.getGlobalBounds().height / 2);
	//opponent level
	opp_lvl.setString("");
	opp_lvl.setString("LVL: "+std::to_string(opplvl));
	opp_lvl.setFont(font);
	opp_lvl.setFillColor(sf::Color::Black);
	opp_lvl.setOrigin(opp_lvl.getGlobalBounds().width / 2, opp_lvl.getGlobalBounds().height / 2);
	opp_lvl.setCharacterSize(25);
	opp_lvl.setPosition(0, 0);
	opp_lvl.setPosition(window.getSize().x / 2 + 3 * window.getSize().x / 25, window.getSize().y / 2 + window.getSize().y / 15 + star.getGlobalBounds().height / 2);

	//run button
	if (game_mode == 'w') {//only possible to run in wild mode 
		run_sprite = running_sprite;
		run_sprite.setOrigin(run_sprite.getLocalBounds().width / 2, run_sprite.getLocalBounds().height / 2);
		run_text.setString("");
		run_text.setString("run");
		run_text.setFillColor(sf::Color::Black);
		run_text.setFont(font);
		run_text.setCharacterSize(20);
		run_text.setOrigin(run_text.getGlobalBounds().width /2, run_text.getGlobalBounds().height / 2);
		run_text.setPosition(0, 0);
		run_text.setPosition(window.getSize().x * 8/9 , window.getSize().y *8/9);
		run_sprite.setPosition(run_text.getPosition().x, run_text.getPosition().y-run_sprite.getGlobalBounds().height/2); //bottom left corner
	}

}
	


void StateFunctions1::draw_state1(sf::RenderWindow& window, Pokemon_Button* buttons[]) {
	
	//text elements
	window.draw(intro_text);
	window.draw(choose_pokemon);
	//how to play
	window.draw(info_text);

	//star+opponent
	window.draw(star);
	window.draw(opp);
	window.draw(opp_name);
	window.draw(opp_lvl);

	//buttons
	if (buttons[0])buttons[0]->draw(window);
	if (buttons[1])buttons[1]->draw(window);
	if (buttons[2])buttons[2]->draw(window);

	//how to play

	//run
	if (mode == 'w') {
		window.draw(run_text);
		window.draw(run_sprite);
	}
}


void StateFunctions1::update_state1(sf::RenderWindow& window, sf::Clock& clock, Pokemon_Button* buttons[], int& clicked_button) {

	star.rotate(2);
	
	if ((sf::Event::MouseMoved) || (sf::Event::MouseButtonPressed)) {
		sf::Vector2i mousepixel = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_pos = window.mapPixelToCoords(mousepixel);

		//check for clicked pokemon buttons
		for (int i = 0; i < 3; i++) {
			if (buttons[i]) {
				(*buttons[i]).update_mouse(mouse_pos, clicked_button);
			}
			else {
			}
		}

		//check for clicked run button
		if (mode == 'w') {
			if (run_sprite.getGlobalBounds().contains(mouse_pos)) {
				run_sprite.setScale(1.2, 1.2); // slightly bigger when the mouse is on the button
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					clicked_button = -1;
				}
			}
			else {
				run_sprite.setScale(1, 1);
			}
		}
		
		//check for clicked how to play button
		if (info_text.getGlobalBounds().contains(mouse_pos)) {
			info_text.setCharacterSize(26); // slightly bigger when the mouse is on the button
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				info_text.setCharacterSize(25);
				clicked_button = 3;
			}
			else {
				info_text.setCharacterSize(25);
			}
		}
	}


}

void StateFunctions1::initialise_countdown(sf::RenderTarget& window){
	text.setString("3");
    text.setCharacterSize(max_char_size);
    font.loadFromFile("fights/upheavtt.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
	text.setPosition(0,0);
    text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height);
    text.move(window.getSize().x/2 , 2*window.getSize().y/5);
    bool draw_count = true;
}

void StateFunctions1::shrink_text(sf::Text& text, float deltatime){
	float add_font_size = 5 * deltatime * max_char_size / 2 ; // must be in proportion to how long its on the screen for
                                                                // i.e. we're on screen for 4/10 = 2/5 of a second
    int font_size = (int)text.getCharacterSize() - (int)add_font_size ;
	if(font_size<1){font_size = 1;}
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
		text.setPosition(0,0);	// centres the 'go' (different size to the numbers)
		text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height);
    	text.move(window.getSize().x/2 , 2*window.getSize().y/5);
	}
	else if (time.asSeconds()>4){
			text.setString("3");//for the next time we call it
		return 2;
	}
	return 10;
}

//------------------------------------------------------------------------------------------------------------

void StateFunctions56::fall(Pokemon* eevee, float& groundY, float& deltaTime) {//make player fall if it is still in the air
	if ((*eevee).y < groundY) {

		(*eevee).velocityY += 981.0f * deltaTime;
		(*eevee).y += (*eevee).velocityY * deltaTime;
		(*eevee).sprite.setPosition((*eevee).x, (*eevee).y);

		if ((*eevee).y >= groundY) {
			(*eevee).y = groundY;
			(*eevee).velocityY = 0.0f;
		}

	}
}

void StateFunctions56::initialize_state_5_6(char game_mode, Pokemon* poke, sf::Font font, sf::Text& text_fainted, sf::Text& choose_pokemon, sf::Text& leave_fight, sf::RenderWindow& target, Pokemon_Button* buttons[], sf::Sprite& running_sprite) {

	//the menu is almost the same when we play against a wild pokemon or a trainer
	//the difference is that we cannot escape against a trainer
	//hence in 't' mode there is no run button and pokemon buttons are placed at the center

	if ((*poke).health.health <= 0) {
		text_fainted.setString((*poke).name + " fainted!");
	}else{
		text_fainted.setString((*poke).enemy->name + " fainted!");
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
	//std::cout <<"buttons[0]"<< buttons[0] << std::endl;
	if (buttons[0]) buttons[0]->setPosition(target.getSize().x / placement, target.getSize().y * 7/16 );
	if (buttons[1]) buttons[1]->setPosition(target.getSize().x / placement, target.getSize().y * 9/16 );
	if (buttons[2]) buttons[2]->setPosition(target.getSize().x / placement, target.getSize().y * 11/16 );


	//update life of the pokemon on its button
	//std::cout << "index"<<poke->index << std::endl;
	std::cout << buttons[(*poke).index] << std::endl;
	buttons[(*poke).index]->setHealth((*poke).health.health);
	//std::cout << "just set life" << std::endl;
}

void const StateFunctions56::draw_state_5_6(char game_mode,  sf::Font& font, sf::Text& text_fainted, sf::Text choose_pokemon, sf::Text leave_fight, sf::RenderWindow& target, Pokemon_Button* buttons[], sf::Sprite& running_sprite) {
	//text elements
	choose_pokemon.setFont(font);//for some reason I need to reset the font here otherwise it throws some exceptions I am not able to fix
	text_fainted.setFont(font);
	target.draw(text_fainted);
	target.draw(choose_pokemon);


	//buttons
	if (buttons[0])buttons[0]->draw(target);
	if (buttons[1])buttons[1]->draw(target);
	if (buttons[2])buttons[2]->draw(target);


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
			//std::cout << "checked for clicked buttons" << std::endl;
			if (buttons[i]) {
				(*buttons[i]).update_mouse(mouse_pos, clicked_button);
			}
		}

		if (game_mode == 'w') {
			//check for clicked run button
			//would be nice to make it 'pixel perfect'
			if (running_sprite.getGlobalBounds().contains(mouse_pos)) {
				running_sprite.setScale(2.2, 2.2); // slightly bigger when the mouse is on the button
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					//std::cout << "you pressed the run button" << std::endl;
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

void StateFunctions56::initialize_state_8(Pokemon* poke, sf::Font& font, sf::Text& text_fainted, sf::RenderWindow& window) {

	text_fainted.setString(poke->name + " fainted!");
	text_fainted.setFont(font);
	text_fainted.setCharacterSize(50);
	text_fainted.setFillColor(sf::Color::Black);
	text_fainted.setOrigin(text_fainted.getGlobalBounds().width / 2, text_fainted.getGlobalBounds().height / 2);
	text_fainted.setPosition(window.getSize().x / 2, window.getSize().y / 9);

	//maybe add a button to leave ?

}

StateFunctions56::StateFunctions56(){
	onquit = false;
	offquit = false;
}

bool StateFunctions56::check_leave(sf::Sprite &arrow_sprite, sf::RenderWindow& window) {
	sf::Vector2i mousepixel = sf::Mouse::getPosition(window);
	sf::Vector2f mouse_pos = window.mapPixelToCoords(mousepixel);
	if ((arrow_sprite.getGlobalBounds().contains(mouse_pos))&& !(onquit)) {
		arrow_sprite.setScale(arrow_sprite.getScale().x*1.2, arrow_sprite.getScale().y*1.2);
		onquit = true;
		offquit = false;} // slightly bigger when the mouse is on the button
	else if (!(arrow_sprite.getGlobalBounds().contains(mouse_pos))&& !(offquit)){
		arrow_sprite.setScale(arrow_sprite.getScale().x/1.2, arrow_sprite.getScale().y/1.2);
		offquit = true;
		onquit = false;}

	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left))&&(arrow_sprite.getGlobalBounds().contains(mouse_pos))) {
		//std::cout << "you pressed the run button" << std::endl;
		return true;
	}
	return false;
}

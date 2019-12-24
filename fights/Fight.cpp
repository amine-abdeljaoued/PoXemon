#include "Fight.h"

Fight::Fight(){
    state = 1;
    if (!font.loadFromFile("upheavtt.ttf")) { std::cout << "could not load font" << std::endl; }
	else {font.loadFromFile("upheavtt.ttf");}
}

Fight::Fight(sf::RenderWindow& window){
    if (!font.loadFromFile("upheavtt.ttf")) { std::cout << "could not load font" << std::endl; }
	else {font.loadFromFile("upheavtt.ttf");}
    state = 1;

    // States 5,6
    leave_fight.setString("Run");
	choose_pokemon.setString("Choose your next pokemon");
    if (!running.loadFromFile("Images/running_trainer.png"))std::cout << "could open running trainer" << std::endl;
	running.loadFromFile("Images/running_trainer.png");
	running_sprite.setTexture(running);
	running_sprite.setScale(2, 2);
	running_sprite.setOrigin(running_sprite.getLocalBounds().width / 2, running_sprite.getLocalBounds().height / 2);
    running_sprite.setPosition(window.getSize().x *2/ 3, window.getSize().y / 2);

	// shader + box for blur effect
	box.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    box.setFillColor(sf::Color(0,0,0,64));
    if(!shader.loadFromFile("Blur2.frag", sf::Shader::Fragment)){std::cout<<"no shader"<<std::endl;}
    shader.setUniform("offsetFactor", sf::Vector2f(0,0.007));
}

void Fight::initialise(char& mode, Backpack& pbag, Backpack& popponent_bag, Player* player, Opponent* opponent, sf::RenderWindow& window){
    // background - must change depending on where we are
    functions1.initialise_background(window, "Images/grassbg.png", background, BackgroundTexture);
    // basic set up
    bag = pbag;
    opponent_bag = popponent_bag;
    game_mode = mode;
    pplayer = player;
    popponent = opponent;
    for (int i=0; i<3; i++){
        poke_buttons[i] =  &((bag.backpack_pokemons[i])->button);
    }
    (bag).set_opponent(popponent);
    (*pplayer).set_enemy(popponent);
	(*popponent).set_enemy(pplayer);

    // for state 1
    state = 1;
	functions1.initialise(*popponent, *player, window, font);

    // states 2,5,6
    deltaTime = 0.0f;
    counter = 0;

    // states 5,6
    clicked_button = -2; // no button clicked  
}

int Fight::update(sf::RenderWindow& window){
    deltaTime = clock.restart().asSeconds();
    elapsed = clock_regenerate_bullets.getElapsedTime();
    elapsed2 = clock2.getElapsedTime();
	attack_1_time = attack_1_clock.getElapsedTime();
	attack_2_time = attack_2_clock.getElapsedTime();
	attack_3_time = attack_3_clock.getElapsedTime();

	if (state==1){ // Initial game menu 
		state = functions1.update_state1(window, clock_regenerate_bullets);
		window.clear();
		window.draw(background);
		functions1.draw1(window);
		// we should be able to choose our pokemon...
	}

	else if (state==10){ // countdown
		state = functions1.countdown(window, deltaTime, elapsed);
		window.clear();
		functions1.draw_blurry_background(window, background, box, bag, *pplayer, *popponent, &shader);
		window.draw(functions1.text);
	}

	else if (state==2){ // fight
		(*pplayer).update(deltaTime, window, clock, elapsed, attack_1_time, 
						attack_2_time, attack_3_time, attack_1_clock, attack_2_clock, attack_3_clock, groundY);
		(*popponent).update(deltaTime, window, clock, elapsed, attack_1_time_opp, 
						attack_2_time_opp, attack_3_time_opp, attack_1_clock_opp, attack_2_clock_opp, attack_3_clock_opp, groundY);

		//player dies
		if ((*pplayer).health.health <= 0) {

			(bag).backpack_pokemons[(*pplayer).index]->health = 0; //set health of the corresponding backpack pokemon to 0

			if (!(bag).alive_pokemons()) { // no more alive pokemons
				if (game_mode == 't') { //lost the duel
					functions56.initialize_state7(false, wonlost, font, window);
					won = false;
					state = 7;
				}
				else {//lost against a wild pokemon
					functions56.initialize_state_8((*pplayer), font, text_fainted, window);
					won = false;
					state = 8;
				}
			}

			else {
				functions56.initialize_state_5_6(game_mode, (*pplayer), font, text_fainted, choose_pokemon, leave_fight, window, poke_buttons, running_sprite);
				state = 5;
			}
		}

		//opponent dies
		if ((*popponent).health.health <= 0) {
			(opponent_bag).backpack_pokemons[(*popponent).index]->health = 0;
			(bag).backpack_pokemons[(*pplayer).index]->health = (*pplayer).health.health;//update health of our pokemon in the backpack

			if (game_mode == 't') { //if we are playing against a trainer

				if (! (opponent_bag).alive_pokemons()) { //all of the trainer's pokemons are dead -> we won the duel
					std::cout << "you won !!!" << std::endl;
					functions56.initialize_state7(true, wonlost, font, window);
					won = true;
					state = 7;
				}

				else { //the trainer still has pokemons -> he takes the next one
					functions56.initialize_state_5_6(game_mode, (*pplayer), font, text_fainted, choose_pokemon, leave_fight, window, poke_buttons, running_sprite);
					//initialize_next_opp(); // create a text + image : you are about to fight 'next opponent'
					state = 6;
				}

			}
			else // (game_mode == 'w')
			{
				won = true;
				functions56.initialize_state_8((*popponent), font, text_fainted, window);
				state = 8;

				//text element : 'opponent fainted'
				//text element : you won the fight against
				//gained xp...
				//go back to map
			}

		}

		(bag).Pokeball_shoot(deltaTime, window, clock2, elapsed2);
		window.clear(sf::Color::Blue);
		window.draw(background);
		(bag).draw(window);
		(*pplayer).draw(window);
		(*popponent).draw(window);
	}

	else if (state == 5) {//player dies

		(*pplayer).death_disappear(deltaTime);
		//make gravity work 
		functions56.fall((*pplayer), groundY, deltaTime);
		functions56.fall((*popponent), groundY, deltaTime);

		//bullets that were shot before the end continue their movement
		(*pplayer).bullets.update(window, deltaTime, clock, elapsed, attack_1_time, attack_2_time, attack_3_time, attack_1_clock, 
							attack_2_clock, attack_3_clock, (*popponent).sprite, groundY);
		(*popponent).bullets.update(window, deltaTime, clock, elapsed, attack_1_time_opp, 
						attack_2_time_opp, attack_3_time_opp, attack_1_clock_opp, attack_2_clock_opp, attack_3_clock_opp,
						(*popponent).sprite, groundY);

		//draw stuff
		window.clear(sf::Color::Blue);
		functions1.draw_blurry_background(window, background, box, bag, *pplayer, *popponent, &shader);

		//draw the menu
		//maybe we should wait a few seconds before drawing this
		functions56.update_state_5_6(game_mode, window, poke_buttons, clicked_button, running_sprite);//check for clicked buttons
		functions56.draw_state_5_6(game_mode, font, text_fainted, choose_pokemon, leave_fight, window, poke_buttons, running_sprite);

		if (clicked_button >= 0) {//we clicked on a pokemon button
			delete pplayer;
			Player* pplayer = new Player(10.f, groundY, 200.f, 500.f, *(bag.backpack_pokemons[clicked_button]));//reinitialize player with the chosen pokemon
			(*popponent).x = 1000.f;//reset opponent's position
			(bag).set_opponent(popponent);
			//dont forget to reset enemies
			(*pplayer).set_enemy(popponent);
			(*popponent).set_enemy(pplayer);

			state = 2;//go back to fight
			clicked_button = -2;//set it unclicked
		}

		if (clicked_button == -1) {//we clicked on the run button
			delete pplayer;
			delete popponent;
			//black screen
			//go back to where we were on the map
		}
	}

	else if (state == 6) { //(game mode 'w') opponent dies and trainer still has pokemons

		(*popponent).death_disappear(deltaTime);
		functions56.fall((*pplayer), groundY, deltaTime);
		functions56.fall((*popponent), groundY, deltaTime);
		(*pplayer).bullets.update(window, deltaTime, clock, elapsed, attack_1_time, attack_2_time, attack_3_time, attack_1_clock, 
							attack_2_clock, attack_3_clock, (*popponent).sprite, groundY);
		(*popponent).bullets.update(window, deltaTime, clock, elapsed, attack_1_time_opp, 
						attack_2_time_opp, attack_3_time_opp, attack_1_clock_opp, attack_2_clock_opp, attack_3_clock_opp,
						(*popponent).sprite, groundY);

		window.clear(sf::Color::Blue);
		functions1.draw_blurry_background(window, background, box, bag, *pplayer, *popponent, &shader);

		int index = (*popponent).index;
		//you are about to fight + 'opponent'
		//have an image, text etc...

		
		functions56.update_state_5_6(game_mode, window, poke_buttons, clicked_button, running_sprite);//check for clicked buttons
		functions56.draw_state_5_6(game_mode, font, text_fainted, choose_pokemon, leave_fight, window, poke_buttons, running_sprite);

		if (clicked_button >= 0) {//we clicked on a pokemon button
			delete pplayer;//maybe it would be better not to delete it if we chose the same ?
			Player* pplayer = new Player(10.f, groundY, 200.f, 500.f, *(bag.backpack_pokemons[clicked_button]));//reinitialize player with the chosen pokemon
			
			delete popponent;
			Opponent* popponent = new Opponent(1000.f, groundY, 200.f, 500.f, *(opponent_bag.backpack_pokemons[index+1]));//reinitialize opponent with the next one in the trainer's bag //change it randomly ?

			(bag).set_opponent(popponent);
			//dont forget to reset enemies
			(*pplayer).set_enemy(popponent);
			(*popponent).set_enemy(pplayer);

			state = 2;//go back to fight
			clicked_button = -2;//set it unclicked
		}

	}

	else if (state == 7) { //end of the duel against a trainer

	// won == true: no more alive opponent pokemons -> we won the duel
	// won == false: no more alive player pokemons -> we lost the duel

		if (won) {
			(*popponent).death_disappear(deltaTime);
		}
		else {
			(*pplayer).death_disappear(deltaTime);
		}

		//make gravity work 
		functions56.fall((*pplayer), groundY, deltaTime);
		functions56.fall((*popponent), groundY, deltaTime);
		//bullets that were shot before the end continue their movement
		(*pplayer).bullets.update(window, deltaTime, clock, elapsed, attack_1_time, attack_2_time, attack_3_time, attack_1_clock, 
							attack_2_clock, attack_3_clock, (*popponent).sprite, groundY);
		(*popponent).bullets.update(window, deltaTime, clock, elapsed, attack_1_time_opp, 
						attack_2_time_opp, attack_3_time_opp, attack_1_clock_opp, attack_2_clock_opp, attack_3_clock_opp,
						(*popponent).sprite, groundY);
		//draw stuff
		window.clear(sf::Color::Blue);
		functions1.draw_blurry_background(window, background, box, bag, *pplayer, *popponent, &shader);


		window.draw(wonlost);
		return 0;
	}

	else if (state == 8) { //end of the fight against a wild pokemon

		if (won) {
			(*popponent).death_disappear(deltaTime);
		}
		else {
			(*pplayer).death_disappear(deltaTime);
		}
		//make gravity work 
		functions56.fall((*pplayer), groundY, deltaTime);
		functions56.fall((*popponent), groundY, deltaTime);
		//bullets that were shot before the end continue their movement
		(*pplayer).bullets.update(window, deltaTime, clock, elapsed, attack_1_time, attack_2_time, attack_3_time, attack_1_clock, 
							attack_2_clock, attack_3_clock, (*popponent).sprite, groundY);
		(*popponent).bullets.update(window, deltaTime, clock, elapsed, attack_1_time_opp, 
						attack_2_time_opp, attack_3_time_opp, attack_1_clock_opp, attack_2_clock_opp, attack_3_clock_opp,
						(*popponent).sprite, groundY);
		//draw stuff
		window.clear(sf::Color::Blue);
		functions1.draw_blurry_background(window, background, box, bag, *pplayer, *popponent, &shader);

		window.draw(text_fainted);
		//to be completed
		return 0;

	} //wild opponent fainted
    return 1;
}
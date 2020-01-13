#include "Fight.h"

Fight::Fight(){
    state = 1;
    if (!font.loadFromFile("fights/upheavtt.ttf")) { std::cout << "could not load font" << std::endl; }
	else {font.loadFromFile("fights/upheavtt.ttf");}
}

Fight::~Fight(){
	delete pplayer;
	delete popponent;
}

Fight::Fight(sf::RenderWindow& window){
	clicked_button = -2;

    if (!font.loadFromFile("fights/upheavtt.ttf")) { std::cout << "could not load font" << std::endl; }
	else {font.loadFromFile("fights/upheavtt.ttf");}
    state = 1;
	groundY = 3*window.getSize().y/5;

    // States 5,6
    leave_fight.setString("Run");
	choose_pokemon.setString("Choose your next pokemon");
    if (!running.loadFromFile("fights/Images/running_trainer.png"))std::cout << "could open running trainer" << std::endl;
	running.loadFromFile("fights/Images/running_trainer.png");
	running_sprite.setTexture(running);
	running_sprite.setScale(2, 2);
	running_sprite.setOrigin(running_sprite.getLocalBounds().width / 2, running_sprite.getLocalBounds().height / 2);
    running_sprite.setPosition(window.getSize().x *2/ 3, window.getSize().y / 2);

	//Leave button (used in states when the game is finished)
	leave.setString("leave");
	leave.setFont(font);
	leave.setCharacterSize(20);
	leave.setFillColor(sf::Color::Black);
	leave.setOrigin(leave.getGlobalBounds().width / 2, leave.getGlobalBounds().height);
	leave.setPosition(window.getSize().x *9/10 , window.getSize().y *9/10);//bottom left corner
	if (!arrow.loadFromFile("fights/Images/leave_arrow.png"))std::cout << "could open leave_arrow" << std::endl;
	arrow.loadFromFile("fights/Images/leave_arrow.png");
	arrow_sprite.setTexture(arrow);
	arrow_sprite.setScale(0.5, 0.5);
	arrow_sprite.setOrigin(arrow_sprite.getLocalBounds().width / 2, arrow_sprite.getLocalBounds().height/2);
	arrow_sprite.setPosition(window.getSize().x * 9/10, window.getSize().y*9/10 - leave.getGlobalBounds().height/2- arrow_sprite.getGlobalBounds().height / 2);


	// shader for blur effect
    if(!shader.loadFromFile("fights/Blur2.frag", sf::Shader::Fragment)){std::cout<<"no shader"<<std::endl;}
    shader.setUniform("offsetFactor", sf::Vector2f(0,0.001));
}

void Fight::initialise_basic(BackpackMap& pbag_map, sf::RenderWindow& window){
	// background - must change depending on where we are
    functions1.initialise_background(window, "fights/Images/grassbg.png", background, BackgroundTexture);
	std::cout << "ini background" << std::endl;
	// initialise poke_buttons and the fight backpack of our player
    for (int i=0; i<3; i++){
		//std::cout<<i<<std::endl;
		if (pbag_map.backpack_pokemons[i]) {
			poke_buttons[i] = &((pbag_map.backpack_pokemons[i])->button);
			bag.backpack_pokemons[i] = pbag_map.backpack_pokemons[i];
		}
		else{bag.backpack_pokemons[i] = NULL;}
    }

	bag.dict_pokeball["Normalball"] = pbag_map.inventory.find("Normalball")->second;
	bag.dict_pokeball["Superball"] = pbag_map.inventory.find("Superball")->second;
	bag.dict_pokeball["Masterball"] = pbag_map.inventory.find("Masterball")->second;

	// for the states
    state = 1;
	std::cout << "hey state1" << std::endl;

	//functions1.initialise(mode, *popponent, *pplayer, window, font);
	functions1.initialize_state1(game_mode, (*popponent).sprite, (*popponent).name, (*popponent).level, window, poke_buttons, running_sprite, font);
	std::cout << "ini state 1" << std::endl;
    deltaTime = 0.0f;
    counter = 0;
    clicked_button = -2; // no button clicked
}



void Fight::initialise_wild (BackpackMap& pbag_map, sf::RenderWindow& window){
	int type = 10; // must be implemented
    game_mode = 'w';


	// set up players
	Opponent* opponent = get_wild_pokemon(window, type);
	popponent = opponent;

	std::cout << "about to initialize_basic" << std::endl;
	initialise_basic(pbag_map, window);
	std::cout << "initialized basic" << std::endl;
	//pplayer = new Player(window, 200.f, 500.f, *pbag_map.backpack_pokemons[0]);
	//BAGCHECK: random level based on our level

	//when we enconter a pokemon in the wild, it should have a level close to our pokemons
	//we take the average of the levels of the pokemon and add a random integer between 5 and -5
	int nb_pokemons = 0;
	int sum_level = 0;
	for (int i = 0; i < 3; i++) {
		if (bag.backpack_pokemons[i]) {
			nb_pokemons += 1;
			sum_level += bag.backpack_pokemons[i]->level;
		}
	}
	std::cout << nb_pokemons << std::endl;
	std::cout << "computing average" << std::endl;
	float average;
	average = (float)sum_level / (float)nb_pokemons;
	std::cout << "average" << average << std::endl;


	//not very good generation but will do the job
	std::cout << "about to get random_level" << std::endl;
	int difference = (rand() % 7) - 3;
	std::cout << difference << std::endl;
	int random_level = abs((int)round(average) + difference);

	std::cout << "random_level: " << random_level << std::endl;

	popponent->level = random_level;


    bag.set_opponent(popponent);
    //(*pplayer).set_enemy(popponent);
	//(*popponent).set_enemy(pplayer);

	// create an opponent 'backpack' for the scenario
	Backpack_Pokemon* opoke1 = new Backpack_Pokemon((*opponent).name, (*opponent).level, (*opponent).index, (*opponent).health.health, (*opponent).type);
	opponent_bag.backpack_pokemons[0] = opoke1;
}

void Fight::initialise_trainer(BackpackMap& pbag_map, Backpack& popponent_bag, sf::RenderWindow& window){
	//std::cout<<"ini";
	// basic setup
	popponent = new Opponent(window, 200.f, 500.f, *popponent_bag.backpack_pokemons[0]);
	//pplayer = new Player(window, 200.f, 500.f, *pbag_map.backpack_pokemons[0]);
	opponent_bag = popponent_bag;
	game_mode = 't';
	initialise_basic(pbag_map, window);

    (bag).set_opponent(popponent);
    //(*pplayer).set_enemy(popponent);
	//(*popponent).set_enemy(pplayer);
	//std::cout<<2;
}

Opponent* Fight::get_wild_pokemon(sf::RenderWindow& window, int type){
	std::cout << "entering get_wild_pokemon" << std::endl;
	// randomly choose an opponent - must be based on where we are
	/*There are:
	- Identifier for the type: 10 - earth (9 pokemons), 20 - water (5), 30 - air (5), 40 - fire (9)*/
	int index; 			// which pokemon we will choose
	std::string name; 	// the pokemon we get
	if (type==10){
		index = rand()%9 + 1;
		name = Earth_Pokemons.find(index)->second;}
	if (type==20){
		index = rand()%5 + 1;
		name = Water_Pokemons.find(index)->second;}
	if (type==30){
		index = rand()%5 + 1;
		name = Air_Pokemons.find(index)->second;}
	if (type==40){
		index = rand()%9 + 1;
		name = Fire_Pokemons.find(index)->second;}
	std::cout << "just set type" << std::endl;


	Opponent* opponent = new Opponent(window, Pokemons.find(name)->second.height, Pokemons.find(name)->second.velocity,
								Backpack_Pokemon(Pokemons.find(name)->second.name, Pokemons.find(name)->second.level,
									Pokemons.find(name)->second.index, Pokemons.find(name)->second.health, Pokemons.find(name)->second.ptype));
	return opponent;
}

int Fight::update(sf::RenderWindow& window, BackpackMap& bag_map){
    deltaTime = clock.restart().asSeconds();
    elapsed = clock_regenerate_bullets.getElapsedTime();
    elapsed2 = clock2.getElapsedTime();

	if (state==1){ // Initial game menu
		//state = functions1.update_state1(window, clock_regenerate_bullets);

		//std::cout << clicked_button << std::endl;
		window.clear();
		window.draw(background);
		//std::cout << "draw background" << std::endl;
		//functions1.draw1(window);
		functions1.draw_state1(window, poke_buttons);
		//std::cout << "draw state 1" << std::endl;
		functions1.update_state1(window, clock, poke_buttons, clicked_button);
		//std::cout << "update state 1 " << std::endl;


		//std::cout << clicked_button << std::endl;

		if (clicked_button == -2) {//not clicked
			state = 1;
		}
		if (0 <= clicked_button && clicked_button < 3) {//we clicked on a pokemon button
			//std::cout << "clicked on a pokemon" << std::endl;
			//remove stuff at the top
			//Backpack_Pokemon new_player = *bag.backpack_pokemons[clicked_button];
			pplayer = new Player(window, 200.f, 500.f, *bag.backpack_pokemons[clicked_button]);
			(bag).set_opponent(popponent);
			(*pplayer).set_enemy(popponent);
			(*popponent).set_enemy(pplayer);
			state = 10;//countdown
		}
		if (clicked_button == -1) {//we clicked on the run button
			return 0;
		}
		if (clicked_button == 3) {//we clicked on how to play
			state = 15;
			clicked_button = -2;
		}

		clock.restart();
	}


	else if (state==15){ // how to menu
		//functions1.howtoplay(window, deltaTime);
		if (functions56.check_leave(functions1.quit, window)){state= 1;}
		window.draw(background, &shader);
		functions1.draw_how_to(window);
	}

	else if (state==10){ // countdown
		state = functions1.countdown(window, deltaTime, elapsed);
		window.clear();
		functions1.draw_blurry_background(window, background, bag, *pplayer, *popponent, &shader);
		window.draw(functions1.text);
	}

	else if (state==2){ // fight

		//check for pokeballs
		if (bag.new_Masterball.in_air || bag.new_Normalball.in_air || bag.new_Superball.in_air) {
			state = 9;
		}

		(*pplayer).update(deltaTime, window, clock_regenerate_bullets, elapsed, attack_1_clock, attack_2_clock, attack_3_clock, groundY);
		(*popponent).update(deltaTime, window, clock_regenerate_bullets, elapsed,
							attack_1_clock_opp, attack_2_clock_opp, attack_3_clock_opp, groundY);
		window.clear(sf::Color::Blue);
		window.draw(background);
		if (game_mode == 'w'){//we can only throw pokeballs at wild pokemons
			ReturnValue value = bag.Pokeball_shoot(deltaTime, window, clock2, elapsed2); // BAGCHECK - control no of pokeballs
			if (value.string!="None"){
				bag_map.inventory.find(value.string)->second -= 1;
				}

			bag.draw(window);
		}

		(*pplayer).draw(window);
		(*popponent).draw(window);
		//player dies
		if ((*pplayer).health.health <= 0) {
			bag.backpack_pokemons[(*pplayer).index]->health = 0; //set health of the corresponding backpack pokemon to 0
			bag_map.backpack_pokemons[(*pplayer).index]->health = 0;
			//update opponent's level
			opponent_bag.backpack_pokemons[(*popponent).index]->level++;
			(*popponent).level++;
			(*popponent).health.level++;

			if (!bag.alive_pokemons()) { // no more alive pokemons
				won = false;
				if (game_mode == 't') { //lost the duel
					functions56.initialize_state7(false, wonlost, font, window);
					state = 7;
				}
				else {//lost against a wild pokemon
					functions56.initialize_state_8(pplayer, font, text_fainted, window);
					state = 8;
				}
			}

			else {
        		functions56.initialize_state_5_6(game_mode, pplayer, font, text_fainted, choose_pokemon, leave_fight, window, poke_buttons, running_sprite);
				state = 5;
			}
		}

		//opponent dies
		if ((*popponent).health.health <= 0) {
			(opponent_bag).backpack_pokemons[(*popponent).index]->health = 0;
			bag.backpack_pokemons[(*pplayer).index]->health = (*pplayer).health.health;//update health of our pokemon in the backpack
			bag_map.backpack_pokemons[(*pplayer).index]->health = (*pplayer).health.health;

			//update player's level (when a pokemon wins a fight, its level increases by 1)
			bag.backpack_pokemons[(*pplayer).index]->level++;
			bag_map.backpack_pokemons[(*pplayer).index]->level++;
			(*pplayer).level++;
			poke_buttons[(*pplayer).index]->Levelup();

			if (game_mode == 't') { //if we are playing against a trainer
				if (! (opponent_bag).alive_pokemons()) { //all of the trainer's pokemons are dead -> we won the duel
					functions56.initialize_state7(true, wonlost, font, window);
					won = true;
					state = 7;
				}

				else { //the trainer still has pokemons -> he takes the next one
					functions56.initialize_state_5_6(game_mode, pplayer, font, text_fainted, choose_pokemon, leave_fight, window, poke_buttons, running_sprite);
					//initialize_next_opp(); // create a text + image : you are about to fight 'next opponent'
					state = 6;
				}

			}
      // to check
			else // (game_mode == 'w')
			{
				won = true;
				functions56.initialize_state_8(popponent, font, text_fainted, window);
				state = 8;

				//text element : 'opponent fainted'
				//text element : you won the fight against
				//gained xp...
				//go back to map
			}

		}
	}

	else if (state == 5) {//player dies

		(*pplayer).death_disappear(deltaTime);
		//make gravity work
    	functions56.fall(pplayer, groundY, deltaTime);
		functions56.fall(popponent, groundY, deltaTime);

		//bullets that were shot before the end continue their movement
		(*pplayer).bullets.update(window, deltaTime, clock_regenerate_bullets, elapsed, attack_1_clock,
							attack_2_clock, attack_3_clock, (*popponent).sprite, groundY);
		(*popponent).bullets.update(window, deltaTime, clock_regenerate_bullets, elapsed, attack_1_clock_opp,
							attack_2_clock_opp, attack_3_clock_opp, (*popponent).sprite, groundY);

		//draw stuff
		window.clear(sf::Color::Blue);
		functions1.draw_blurry_background(window, background, bag, *pplayer, *popponent, &shader);

		//draw the menu
		//maybe we should wait a few seconds before drawing this
		functions56.update_state_5_6(game_mode, window, poke_buttons, clicked_button, running_sprite);//check for clicked buttons
		functions56.draw_state_5_6(game_mode, font, text_fainted, choose_pokemon, leave_fight, window, poke_buttons, running_sprite);

		if (clicked_button >= 0) {//we clicked on a pokemon button
			delete pplayer;
			pplayer = new Player(window, 200.f, 500.f, *(bag.backpack_pokemons[clicked_button]));//reinitialize player with the chosen pokemon
			(*popponent).x = 4*window.getSize().x/5;;//reset opponent's position
			(bag).set_opponent(popponent);
			//dont forget to reset enemies
			(*pplayer).set_enemy(popponent);
			(*popponent).set_enemy(pplayer);

			state = 2;//go back to fight
			clicked_button = -2;//set it unclicked
		}

		if (clicked_button == -1) { //we clicked on the run button
			delete pplayer;
			delete popponent;

      	return 0;
			//black screen
			//go back to where we were on the map
		}
	}

	else if (state == 6) { //(game mode 'w') opponent dies and trainer still has pokemons
		(*popponent).death_disappear(deltaTime);
		functions56.fall(pplayer, groundY, deltaTime);
		functions56.fall(popponent, groundY, deltaTime);
		(*pplayer).bullets.update(window, deltaTime, clock_regenerate_bullets, elapsed, attack_1_clock,
							attack_2_clock, attack_3_clock, (*popponent).sprite, groundY);
		(*popponent).bullets.update(window, deltaTime, clock_regenerate_bullets, elapsed,
							attack_1_clock_opp, attack_2_clock_opp, attack_3_clock_opp, (*popponent).sprite, groundY);

		window.clear(sf::Color::Blue);
		functions1.draw_blurry_background(window, background, bag, *pplayer, *popponent, &shader);

		int index = (*popponent).index;
		//you are about to fight + 'opponent'
		//have an image, text etc...


		functions56.update_state_5_6(game_mode, window, poke_buttons, clicked_button, running_sprite);//check for clicked buttons
		functions56.draw_state_5_6(game_mode, font, text_fainted, choose_pokemon, leave_fight, window, poke_buttons, running_sprite);

		if (clicked_button >= 0) {//we clicked on a pokemon button
			delete pplayer;//maybe it would be better not to delete it if we chose the same ?
			pplayer = new Player(window, 200.f, 500.f, *(bag.backpack_pokemons[clicked_button]));//reinitialize player with the chosen pokemon

			delete popponent;
			popponent = new Opponent(window, 200.f, 500.f, *(opponent_bag.backpack_pokemons[index+1]));//reinitialize opponent with the next one in the trainer's bag //change it randomly ?

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
    	functions56.fall(pplayer, groundY, deltaTime);
		functions56.fall(popponent, groundY, deltaTime);
		//bullets that were shot before the end continue their movement
		(*pplayer).bullets.update(window, deltaTime, clock_regenerate_bullets, elapsed, attack_1_clock,
							attack_2_clock, attack_3_clock, (*popponent).sprite, groundY);
		(*popponent).bullets.update(window, deltaTime, clock_regenerate_bullets, elapsed, attack_1_clock_opp,
							attack_2_clock_opp, attack_3_clock_opp,(*popponent).sprite, groundY);
		//draw stuff
		window.clear(sf::Color::Blue);
		functions1.draw_blurry_background(window, background, bag, *pplayer, *popponent, &shader);

		window.draw(wonlost);

		//leave button
		window.draw(arrow_sprite);
		window.draw(leave);
		if(won && functions56.check_leave(arrow_sprite, window)){
			return 55; //won against trainer
		}
		if(!won && functions56.check_leave(arrow_sprite, window)){
			return 50; //lost against trainer
		}
	}

	else if (state == 8) { //end of the fight against a wild pokemon
		if (won) {
			(*popponent).death_disappear(deltaTime);
		}
		else {
			(*pplayer).death_disappear(deltaTime);
		}
		//make gravity work
		functions56.fall(pplayer, groundY, deltaTime);
		functions56.fall(popponent, groundY, deltaTime);
		//bullets that were shot before the end continue their movement
		(*pplayer).bullets.update(window, deltaTime, clock_regenerate_bullets, elapsed, attack_1_clock,
							attack_2_clock, attack_3_clock, (*popponent).sprite, groundY);
		(*popponent).bullets.update(window, deltaTime, clock_regenerate_bullets, elapsed, attack_1_clock_opp,
							attack_2_clock_opp, attack_3_clock_opp, (*popponent).sprite, groundY);
		//draw stuff
		window.clear(sf::Color::Blue);
		functions1.draw_blurry_background(window, background, bag, *pplayer, *popponent, &shader);
		window.draw(text_fainted);

		//leave button
		window.draw(arrow_sprite);
		window.draw(leave);
		if(won && functions56.check_leave(arrow_sprite, window)){
			return 0; //won against wild
		}
		if(!won && functions56.check_leave(arrow_sprite, window)){
			return 60; //lost against wild
		}
		/* if (functions56.check_leave(arrow_sprite, window)) return 0; */

	} //wild opponent fainted

	else if (state == 9) {//pokeball is in air (transition state before knowing if we caught the pokemon) //BAGCHECK

	//draw pokeball and other stuff
		elapsed2 = clock2.getElapsedTime(); // took that from francois but I don't really understand how it works so I use another clock
		window.clear(sf::Color::Blue);
		window.draw(background);
		ReturnValue value  = (bag).Pokeball_shoot(deltaTime, window, clock2, elapsed2); //BAGCHECK - update pokeball

		int c = value.i;
		if (value.string!="None"){
			std::cout<<"before: "<<bag_map.inventory.find(value.string)->second<<std::endl;
			// bag_map.inventory.find(value.string)->second -= 1;
			bag_map.inventory[value.string] -= 1;
			std::cout<<"after: "<<bag_map.inventory.find(value.string)->second<<std::endl;}

		(bag).draw(window);
		(*pplayer).draw(window);
		(*popponent).draw(window);

		//make gravity work
		functions56.fall(pplayer, groundY, deltaTime);
		functions56.fall(popponent, groundY, deltaTime);

		//bullets that were shot before the end continue their movement
		(*pplayer).bullets.update(window, deltaTime, clock_regenerate_bullets, elapsed, attack_1_clock,
			attack_2_clock, attack_3_clock, (*popponent).sprite, groundY);
		(*popponent).bullets.update(window, deltaTime, clock_regenerate_bullets, elapsed, attack_1_clock_opp,
			attack_2_clock_opp, attack_3_clock_opp, (*popponent).sprite, groundY);

		//now check the outcome
		if (c == 1) {//the pokeball worked !
			//to be put in initialize_state_11

			caught.setFont(font);
			caught.setCharacterSize(60);
			caught.setString(popponent->name + " was caught !");
			caught.setFillColor(sf::Color::Black);
			caught.setOrigin(caught.getGlobalBounds().width / 2, caught.getGlobalBounds().height / 2);
			caught.setPosition(window.getSize().x / 2, window.getSize().y / 3);
			//if the backpack is not full add it and print "The pokemon was added to your backpack"
			//else print you will be able to use it at the shop..

			//i don't know which one was thown so i just reset them all (theres probably better things to do)
			state = 11;
		}

		else if (c == 2) {//the pokeball didn't work

			//CREATE SOME FUNCTION
			//to be put in initialize_state_11 or 12
			caught.setFont(font);
			caught.setCharacterSize(30);
			caught.setString("You failed to catch "+ popponent->name);
			caught.setFillColor(sf::Color::Black);
			caught.setOrigin(caught.getGlobalBounds().width / 2, caught.getGlobalBounds().height / 2);
			caught.setPosition(window.getSize().x / 2, window.getSize().y / 5);


			bag.new_Masterball.in_air = false;
			bag.new_Normalball.in_air = false;
			bag.new_Superball.in_air = false;

			state = 12;//we need ta clock for the next state so i took this one arbitrarily
			clock2.restart();
		}

	}

	else if (state == 11) { //we caught the pokemon with the pokeball
		//have some animation (light ?...) to show that we caught the pokemon ?
		window.clear(sf::Color::Blue);
		functions1.draw_blurry_background(window, background, bag, *pplayer, *popponent, &shader);

		window.draw(caught);

		//click a button to leave the fight
		bag.new_Masterball.in_air = false;
		bag.new_Normalball.in_air = false;
		bag.new_Superball.in_air = false;

		//leave button
		window.draw(arrow_sprite);
		window.draw(leave);
		if (functions56.check_leave(arrow_sprite, window)) return 0;
	}


	else if (state == 12) {//the pokeball didn't work
		//this is a very short state
		//we only say that the pokeball failed to catch opponent and go back to the countown after 1 second
		functions1.draw_blurry_background(window, background, bag, *pplayer, *popponent, &shader);
		window.draw(caught);
		if (clock2.getElapsedTime().asSeconds() > 1.0f) {
			clock_regenerate_bullets.restart();//reset this for the countdown
			state = 10; // go back to countdown
		}

	}

	return 1;
}

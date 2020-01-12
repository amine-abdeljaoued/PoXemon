#include "box.hpp"
/* #include "ResourcePath.hpp" */

Box::Box() {
    if (!background.loadFromFile(/* resourcePath() + */ "Sprites/screen_menu.jpg")){
        std::cout<<"error"<<std::endl;
    }
    if (!font.loadFromFile(/* resourcePath() + */ "Fonts/sansation.ttf")) {
        std::cout<<"error"<<std::endl;
    }
    if (!slots.loadFromFile(/* resourcePath() + */ "Sprites/poke_slot.png")) {
        std::cout<<"error"<<std::endl;
    }
    if (!types.loadFromFile(/* resourcePath() + */ "Sprites/poke_type.png")) {
        std::cout<<"error"<<std::endl;
    }
    
    //Set the right column by default when open Backpack
    actual_column = 0;
    
    release = true;
    release_left = true;
    release_right = true;
    release_down_left = true;
    release_up_left = true;
    release_down_right = true;
    release_up_right = true;
    
    //Set Values for the switch of Pokemons
    sw = false;
    swi1 = -1;
    swi2 = -1;
    column = -1;
    
    //Set background texture
    background_screen.setTexture(background);
        
    //Set title Color, Position and Font
    text.setString("Box");
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    
    //For Display of Pokemon in bag
        
    //Set textures for each sprite for pokemon
    empty_slot.setTexture(slots);
    empty_slot.setTextureRect(sf::IntRect(256,274,142,22));
        
    not_selected_slot.setTexture(slots);
    not_selected_slot.setTextureRect(sf::IntRect(256,178,142,22));
        
    selected_slot.setTexture(slots);
    selected_slot.setTextureRect(sf::IntRect(256,202,142,22));
        
    poke_close.setTexture(slots);
    poke_close.setTextureRect(sf::IntRect(18,194,20,20));
        
    poke_open.setTexture(slots);
    poke_open.setTextureRect(sf::IntRect(42,192,20,24));
        
    //Set types textures
    earth.setTexture(types);
    earth.setTextureRect(sf::IntRect(0,17,32,14));
        
    water.setTexture(types);
    water.setTextureRect(sf::IntRect(96,33,32,14));
        
    air.setTexture(types);
    air.setTextureRect(sf::IntRect(64,1,32,14));
        
    fire.setTexture(types);
    fire.setTextureRect(sf::IntRect(64,33,32,14));
        
    selectedPokemon_left = 0;
    selectedPokemon_right = 0;
    
    //Set pokemon
    std::string name1 = "yes";
    std::string name2 = "no";
    std::string name3 = "whynot";
    std::string name4 = "Empty";
    Backpack_Pokemon *poke4 = new Backpack_Pokemon(name1, 1, 3, 50, 10);
    Backpack_Pokemon *poke5 = new Backpack_Pokemon(name2, 1, 3, 60, 20);
    Backpack_Pokemon *poke6 = new Backpack_Pokemon(name3, 1, 3, 70, 30);
    Backpack_Pokemon *poke7 = NULL; //new Backpack_Pokemon(name4, 1, 3, 70, 30);
    Backpack_Pokemon *poke8 = NULL;
    Backpack_Pokemon *poke9 = NULL;
    Backpack_Pokemon *poke10 = NULL;
    Backpack_Pokemon *poke11 = NULL;
    Backpack_Pokemon *poke12 = NULL;
    Backpack_Pokemon *poke13 = NULL;
    box_pokemons[0] = poke4;
    box_pokemons[1] = poke5;
    box_pokemons[2] = poke6;
    box_pokemons[3] = poke7;
    box_pokemons[4] = poke8;
    box_pokemons[5] = poke9;
    box_pokemons[6] = poke10;
    box_pokemons[7] = poke11;
    box_pokemons[8] = poke12;
    box_pokemons[9] = poke13;
    
    cout << box_pokemons[5] << endl;
}

//Function to get the bounds of the window in order to draw at the middle of the window
sf::FloatRect Box::getViewBounds(const sf::View &view)
{
        sf::FloatRect rt;
        rt.left = view.getCenter().x - view.getSize().x/2.f;
        rt.top  = view.getCenter().y - view.getSize().y/2.f;
        rt.width  = view.getSize().x;
        rt.height = view.getSize().y;
        return rt;
}

void Box::draw_background(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer, BackpackMap &backpack) {
    
    sf::FloatRect viewBounds = getViewBounds(view);
    
    //Background
    background_screen.setPosition(viewBounds.left, viewBounds.top);
    background_screen.setScale(4, 4);
    
    //Title
    text.setCharacterSize(15);
    width_title = text.getLocalBounds().width;
    text.setOrigin(sf::Vector2f(width_title/2, 0));
    text.setPosition(viewBounds.left+viewBounds.width/2, viewBounds.top);
    
    window.draw(background_screen);
    window.draw(text);
}

void Box::draw_pokemon(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer, BackpackMap &backpack) {
    
    Moveright(event);
    Moveleft(event);
    Moveup_right(event);
    Movedown_right(event);
    Moveup_left(event);
    Movedown_left(event, backpack);
    switchPoke(backpack, event);
    
    sf::FloatRect viewBounds = getViewBounds(view);
    
    //First part for left column with pokemons in backpack
    
    for (int i=0; i<3; i++) {
        empty_slot.setPosition(viewBounds.left+ 15, viewBounds.top + viewBounds.height/3.8 + (i*24));
        empty_slot.setScale(0.8, 1);
        
        window.draw(empty_slot);
    }
    
    if (actual_column == 0) {
        for (int i=0; i<3; i++) {
            if (backpack.backpack_pokemons[i]) {
                if (i != selectedPokemon_left) {
                    not_selected_slot.setPosition(viewBounds.left+ 15, viewBounds.top + viewBounds.height/3.8 + (i*24));
                    not_selected_slot.setScale(0.8, 1);
                    
                    window.draw(not_selected_slot);
                }
                else {
                    selected_slot.setPosition(viewBounds.left+ 15, viewBounds.top + viewBounds.height/3.8 + (i*24));
                    selected_slot.setScale(0.8, 1);
                    
                    window.draw(selected_slot);
                }
            }
        }
    }
    else {
        for (int i=0; i<3; i++) {
            if (backpack.backpack_pokemons[i]) {
                not_selected_slot.setPosition(viewBounds.left+ 15, viewBounds.top + viewBounds.height/3.8 + (i*24));
                not_selected_slot.setScale(0.8, 1);
                
                window.draw(not_selected_slot);
            }
        }
    }
    
    if (actual_column == 0) {
        for (int i=0; i<3; i++) {
            if (backpack.backpack_pokemons[i]) {
                if (i == selectedPokemon_left) {
                    poke_open.setOrigin(10, 12);
                    poke_open.setPosition(viewBounds.left+15, viewBounds.top + viewBounds.height/3.8 +(i*24) + 11);
                    
                    window.draw(poke_open);
                }
                else {
                    poke_close.setOrigin(10, 10);
                    poke_close.setPosition(viewBounds.left+15, viewBounds.top + viewBounds.height/3.8 +(i*24) +11);
                
                    
                    window.draw(poke_close);
                }
            }
        }
    }
    else {
        for (int i=0; i<3; i++) {
            if (backpack.backpack_pokemons[i]) {
                poke_close.setOrigin(10, 10);
                poke_close.setPosition(viewBounds.left+15, viewBounds.top + viewBounds.height/3.8 +(i*24) +11);
                
                window.draw(poke_close);
            }
        }
    }
    
    //Draw health bar
    for (int i=0; i<3; i++) {
        if (backpack.backpack_pokemons[i]) {
            sf::RectangleShape health_bar;
            health_poke = (float) (backpack.backpack_pokemons[i]->health)/100;
            health_bar.setSize(sf::Vector2f(38.5*health_poke,3));
            health_bar.setPosition(viewBounds.left+85.5, viewBounds.top + viewBounds.height/3.8 + (i*24) + 8);
            if (health_poke >= 0.5) {
                health_bar.setFillColor(sf::Color::Green);
            }
            else if (0.2 <= health_poke && health_poke< 0.5){
                health_bar.setFillColor(sf::Color(255,140,0));
            }
            else if (health_poke < 0.2){
                health_bar.setFillColor(sf::Color::Red);
            }
            window.draw(health_bar);
        }
    }
    
    //Draw Names and level of pokemon in backpack
    for (int i=0; i<3; i++) {
        if (backpack.backpack_pokemons[i]) {
            poke_name.setString(backpack.backpack_pokemons[i]->name);
            level.setString("lvl " + toString(backpack.backpack_pokemons[i]->level));
            poke_name.setCharacterSize(10);
            level.setCharacterSize(10);
            //poke_name.setFillColor(sf::Color::White);
            level.setFillColor(sf::Color::White);
            poke_name.setFont(font);
            level.setFont(font);
            poke_name.setPosition(viewBounds.left+30, viewBounds.top + viewBounds.height/3.8 +(i*24));
            level.setPosition(viewBounds.left+40, viewBounds.top + viewBounds.height/3.8 +(i*24)+10);
            
            if (column == 0&&selectedPokemon_1==i) {
                poke_name.setFillColor(sf::Color::Red);
            }
            else {
                poke_name.setFillColor(sf::Color::White);
            }
            
            window.draw(poke_name);
            window.draw(level);
        }
    }
    
    //Draw Pokemon Type
    for (int i=0; i<3; i++) {
        if (backpack.backpack_pokemons[i]){
            if (backpack.backpack_pokemons[i]->type == 10) {
                earth.setScale(0.6, 0.4);
                earth.setPosition(viewBounds.left+95, viewBounds.top+ viewBounds.height/3.8 +(i*24)+14);
                window.draw(earth);
            }
            if (backpack.backpack_pokemons[i]->type== 20) {
                water.setScale(0.6, 0.4);
                water.setPosition(viewBounds.left+95, viewBounds.top+ viewBounds.height/3.8 +(i*24)+14);
                window.draw(water);
            }
            if (backpack.backpack_pokemons[i]->type == 30) {
                air.setScale(0.6, 0.4);
                air.setPosition(viewBounds.left+95, viewBounds.top+ viewBounds.height/3.8 +(i*24)+14);
                window.draw(air);
            }
            if (backpack.backpack_pokemons[i]->type == 40) {
                fire.setScale(0.6, 0.4);
                fire.setPosition(viewBounds.left+95, viewBounds.top+ viewBounds.height/3.8 +(i*24)+14);
                window.draw(fire);
            }
        }
    }
    
    //Second part for right column with pokemons in box
    
    for (int i=0; i<10; i++) {
        empty_slot.setPosition(viewBounds.left+ viewBounds.width/2+17, viewBounds.top + 25 + (i*24));
        empty_slot.setScale(0.8, 1);

        window.draw(empty_slot);
    }

    if (actual_column == 1) {
        for (int i=0; i<10; i++) {
            if (box_pokemons[i]) {
                if (i != selectedPokemon_right) {
                    not_selected_slot.setPosition(viewBounds.left+ viewBounds.width/2+17, viewBounds.top + 25 + (i*24));
                    not_selected_slot.setScale(0.8, 1);

                    window.draw(not_selected_slot);
                }
                else {
                    selected_slot.setPosition(viewBounds.left+ viewBounds.width/2+17, viewBounds.top + 25 + (i*24));
                    selected_slot.setScale(0.8, 1);

                    window.draw(selected_slot);
                }
            }
        }
    }
    else {
        for (int i=0; i<10; i++) {
            if (box_pokemons[i]) {
                not_selected_slot.setPosition(viewBounds.left+ viewBounds.width/2+17, viewBounds.top + 25 + (i*24));
                not_selected_slot.setScale(0.8, 1);

                window.draw(not_selected_slot);
            }
        }
    }

    if (actual_column == 1) {
        for (int i=0; i<10; i++) {
            if (box_pokemons[i]) {
                if (i == selectedPokemon_right) {
                    poke_open.setOrigin(10, 12);
                    poke_open.setPosition(viewBounds.left + viewBounds.width/2+17, viewBounds.top + 25 +(i*24) + 11);

                    window.draw(poke_open);
                }
                else {
                    poke_close.setOrigin(10, 10);
                    poke_close.setPosition(viewBounds.left + viewBounds.width/2+17, viewBounds.top + 25 +(i*24) + 11);


                    window.draw(poke_close);
                }
            }
        }
    }
    else {
        for (int i=0; i<10; i++) {
            if (box_pokemons[i]) {
                poke_close.setOrigin(10, 10);
                poke_close.setPosition(viewBounds.left + viewBounds.width/2+17, viewBounds.top + 25 +(i*24) + 11);

                window.draw(poke_close);
            }
        }
    }

    //Draw health bar
    for (int i=0; i<10; i++) {
        if (box_pokemons[i]) {
            sf::RectangleShape health_bar;
            health_poke = (float) (box_pokemons[i]->health)/100;
            health_bar.setSize(sf::Vector2f(38.5*health_poke,3));
            health_bar.setPosition(viewBounds.left+viewBounds.width/1.292 + 13, viewBounds.top + 25 + (i*24) + 8);
            if (health_poke >= 0.5) {
                health_bar.setFillColor(sf::Color::Green);
            }
            else if (0.2 <= health_poke && health_poke< 0.5){
                health_bar.setFillColor(sf::Color(255,140,0));
            }
            else if (health_poke < 0.2){
                health_bar.setFillColor(sf::Color::Red);
            }
            window.draw(health_bar);
        }
    }

    //Draw Names and level of pokemon in backpack
    for (int i=0; i<10; i++) {
        if (box_pokemons[i]) {
            poke_name.setString(box_pokemons[i]->name);
            level.setString("lvl " + toString(box_pokemons[i]->level));
            poke_name.setCharacterSize(10);
            level.setCharacterSize(10);
//            poke_name.setFillColor(sf::Color::White);
            level.setFillColor(sf::Color::White);
            poke_name.setFont(font);
            level.setFont(font);
            poke_name.setPosition(viewBounds.left+viewBounds.width/1.7 +8, viewBounds.top + 25 +(i*24));
            level.setPosition(viewBounds.left+viewBounds.width/1.7 +18, viewBounds.top + 35 +(i*24));
            
            if (column == 1&&selectedPokemon_1==i) {
                poke_name.setFillColor(sf::Color::Red);
            }
            else {
                poke_name.setFillColor(sf::Color::White);
            }

            window.draw(poke_name);
            window.draw(level);
        }
    }

    //Draw Pokemon Type
    for (int i=0; i<10; i++) {
        if (box_pokemons[i]){
            if (box_pokemons[i]->type == 10) {
                earth.setScale(0.6, 0.4);
                earth.setPosition(viewBounds.left+viewBounds.width/1.5+50, viewBounds.top+ 25 +(i*24)+14);
                window.draw(earth);
            }
            if (box_pokemons[i]->type== 20) {
                water.setScale(0.6, 0.4);
                water.setPosition(viewBounds.left+viewBounds.width/1.5+50, viewBounds.top+ 25 +(i*24)+14);
                window.draw(water);
            }
            if (box_pokemons[i]->type == 30) {
                air.setScale(0.6, 0.4);
                air.setPosition(viewBounds.left+viewBounds.width/1.5+50, viewBounds.top+ 25 +(i*24)+14);
                window.draw(air);
            }
            if (box_pokemons[i]->type == 40) {
                fire.setScale(0.6, 0.4);
                fire.setPosition(viewBounds.left+viewBounds.width/1.5+50, viewBounds.top+ 25 +(i*24)+14);
                window.draw(fire);
            }
        }
    }
}

void Box::draw(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer, BackpackMap &backpack) {
    if (trainer.state == "Box") {
        draw_background(window, view, event, trainer, backpack);
        draw_pokemon(window, view, event, trainer, backpack);
    }
}

void Box::Moveup_left(sf::Event &event) {
    if (actual_column==0) {
        if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Up&&release_up_left == true){
            if (selectedPokemon_left > 0) {
                selectedPokemon_left--;
            }
            release_up_left = false;
        }
        else if (event.type == sf::Event::KeyReleased&&event.key.code == sf::Keyboard::Up){
            release_up_left = true;
        }
    }
}

void Box::Movedown_left(sf::Event &event, BackpackMap &backpack) {
    if (actual_column==0) {
        if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Down&&release_down_left == true){
            if (selectedPokemon_left < 2 && backpack.backpack_pokemons[selectedPokemon_left+1]) {
                selectedPokemon_left++;
            }
            release_down_left = false;
        }
        else if (event.type == sf::Event::KeyReleased&&event.key.code == sf::Keyboard::Down){
            release_down_left = true;
        }
    }
}

void Box::Moveup_right(sf::Event &event) {
    if (actual_column==1) {
        if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Up&&release_up_right == true){
            if (selectedPokemon_right - 1 >= 0) {
                selectedPokemon_right--;
            }
            release_up_right = false;
        }
        else if (event.type == sf::Event::KeyReleased&&event.key.code == sf::Keyboard::Up){
            release_up_right = true;
        }
    }
}

void Box::Movedown_right(sf::Event &event) {
    if (actual_column == 1) {
        if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Down&&release_up_right == true){
            if (selectedPokemon_right + 1 <= 9 && box_pokemons[selectedPokemon_right+1]) {
                selectedPokemon_right++;
            }
            release_up_right = false;
        }
        else if (event.type == sf::Event::KeyReleased&&event.key.code == sf::Keyboard::Down){
            release_up_right = true;
        }
    }
}

void Box::Moveleft(sf::Event &event) {
    if (actual_column==1) {
        if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Left&&release == true){
            actual_column = 0;
            release_left = false;
        }
        else if (event.type == sf::Event::KeyReleased&&event.key.code == sf::Keyboard::Left){
            release_left = true;
        }
    }
}

void Box::Moveright(sf::Event &event) {
    if (actual_column==0) {
        if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Right&&release == true){
            actual_column = 1;
            release_right = false;
        }
        else if (event.type == sf::Event::KeyReleased&&event.key.code == sf::Keyboard::Right){
            release_right = true;
        }
    }
}

bool Box::pointerEmpty(int i){
    return (box_pokemons[i] == NULL);
}

bool Box::addPokemonB(std::string name, int level, int index, int health, int type){
    bool in = false;
    int i = 0;
    while(i<10 && in == false){
        if (pointerEmpty(i) == true){
            box_pokemons[i] = new Backpack_Pokemon(name,level,index,health,type);
            poke_list.push_back(name);
            in = true;
            return in;
        }
        i++;
    }
    return false;
}

bool Box::addPokemon(Backpack_Pokemon poke, BackpackMap &backpack){
    //Unpacking
    string name = poke.name;
    int level = poke.level;
    int index = poke.index;
    int health = poke.health;
    int type = poke.type;
    bool in = false;
    int i = 0;
    while(i<2 && in == false){
        if (backpack.backpack_pokemons[i] == NULL){
            backpack.backpack_pokemons[i] = new Backpack_Pokemon(name,level,index,health,type);
            in = true;
            return in;
        }
        i++;
    }
    return addPokemonB(name, level, index, health, type);
}


void Box::switchPoke(BackpackMap &backpack, sf::Event &event){
    if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::X&&sw==false){
        sw = true;
        if (actual_column == 0) {
            selectedPokemon_1 = selectedPokemon_left;
        }
        else {
            selectedPokemon_1 = selectedPokemon_right;
        }
        swi1 = selectedPokemon_1;
        column = actual_column;
    }
    if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::X&&sw==true&&actual_column!=column){
        if (actual_column == 0) {
            selectedPokemon_2 = selectedPokemon_left;
        }
        else {
            selectedPokemon_2 = selectedPokemon_right;
        }
        swi2 = selectedPokemon_2;
        
        if (column == 0) {
            Backpack_Pokemon* tempP = backpack.backpack_pokemons[swi1];
            backpack.backpack_pokemons[swi1] = box_pokemons[swi2];
            box_pokemons[swi2] = tempP;
            
            backpack.backpack_pokemons[swi1]->index = swi2;
            box_pokemons[swi2]->index = 3;
        }
        else {
            Backpack_Pokemon* tempP = box_pokemons[swi1];
            box_pokemons[swi1] = backpack.backpack_pokemons[swi2];
            backpack.backpack_pokemons[swi2] = tempP;
            
            backpack.backpack_pokemons[swi1]->index = swi1;
            box_pokemons[swi2]->index = 3;
        }
        
        sw = false;
        swi1 = -1;
        swi2 = -1;
        column = -1;
    }
}

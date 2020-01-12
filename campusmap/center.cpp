#include "center.hpp"

Center::Center(){
    Selecteditem = 0;
    arrow = true;
    action_list = {"Heal", "Switch Pokemon", "Pokemon Box"};
    pokemon_bag = {"jistolwer","auron","husabus"};
    
    if (!font.loadFromFile(/* resourcePath() + */ "Fonts/sansation.ttf")) {
        std::cout<<"Problem"<<std::endl;
    }
    
    counter = 0;
    interface = {action_list,pokemon_bag};
        
    //switch
    sw = false;
    swi1 = -1;
    swi2 = -1;
}

void Center::draw(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer, BackpackMap &backpack){
    if (trainer.state == "Healing"){
        Moveup(event);
        Movedown(event);
        
        sf::FloatRect viewBounds = getViewBounds(view);
        
        sf::Text text[interface[counter].size()];
        for (int i=0; i < interface[counter].size(); i++){
            text[i].setCharacterSize(10);
            text[i].setFillColor(sf::Color::Black);
            text[i].setFont(font);
            text[i].setPosition(4+ viewBounds.width/2 + viewBounds.left, viewBounds.top + 10*i + 4);
            text[i].setString(interface[counter][i]);
        }
        
        text[Selecteditem].setFillColor(sf::Color::Red);
        
        if (sw == true){
            if (swi1>=0){
                text[swi1].setFillColor(sf::Color::Red);
            }
            if (swi2>=0){
                text[swi2].setFillColor(sf::Color::Red);
            }
        }
        sf::RectangleShape rect(sf::Vector2f(viewBounds.width/2, viewBounds.height/3));
        rect.setFillColor(sf::Color::White);
        rect.setOutlineThickness(2);
        rect.setOutlineColor(sf::Color::Black);
        rect.setPosition(sf::Vector2f(viewBounds.left + viewBounds.width/2 -2, viewBounds.top + 2));
        window.draw(rect);
        
        for(int i=0; i < interface[counter].size(); i++){
            window.draw(text[i]);
        }
        heal_pokemons(backpack, event, trainer);
        switchMenu(window, backpack, event, view, trainer);
        switchPokemon(window, backpack, event, view, trainer);
    }
}



sf::FloatRect Center::getViewBounds(const sf::View &view)
{
        sf::FloatRect rt;
        rt.left = view.getCenter().x - view.getSize().x/2.f;
        rt.top  = view.getCenter().y - view.getSize().y/2.f;
        rt.width  = view.getSize().x;
        rt.height = view.getSize().y;
        return rt;
}

void Center::Moveup(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Up&&arrow == true){
        if (Selecteditem - 1 >= 0) {
            Selecteditem--;
        }
        arrow = false;
    }
    else if (event.type == sf::Event::KeyReleased&&event.key.code == sf::Keyboard::Up){
        arrow = true;
    }
}

void Center::Movedown(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Down&&arrow == true){
        if (Selecteditem + 1 <= interface[counter].size() - 1) {
            Selecteditem++;
        }
        arrow = false;
    }
    else if (event.type == sf::Event::KeyReleased&&event.key.code == sf::Keyboard::Down){
        arrow = true;
    }
}

    
void Center::heal_pokemons(BackpackMap &backpack, sf::Event &event, Trainer &trainer) {
    if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::X&&Selecteditem == 0&&counter == 0){
        for (unsigned int i = 0; i < 3; i++) {
            backpack.backpack_pokemons[i]->health = 100;
        }
        trainer.state = "Stop";
        counter = 0;
        swi1 = -1;
        swi2 = -1;
        sw = false;
    }
}

void Center::switchMenu(sf::RenderWindow &window, BackpackMap &backpack, sf::Event &event, sf::View &view, Trainer &trainer){
    if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::X&&Selecteditem == 1&&counter == 0){
        counter++;
        Selecteditem = 0;
    }
}

void Center::switchPokemon(sf::RenderWindow &window, BackpackMap &backpack, sf::Event &event, sf::View &view, Trainer &trainer){
    if (counter == 1){
        if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::X&&sw==false){
            sw = true;
            swi1 = Selecteditem;
        }
        if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::X&&sw==true&&Selecteditem!=swi1){
            swi2 = Selecteditem;
            
            string temp = interface[counter][swi1];
            interface[counter][swi1] = interface[counter][swi2];
            interface[counter][swi2] = temp;
            
            Backpack_Pokemon* tempP = backpack.backpack_pokemons[swi1];
            backpack.backpack_pokemons[swi1] = backpack.backpack_pokemons[swi2];
            backpack.backpack_pokemons[swi2] = tempP;
            
            backpack.backpack_pokemons[swi1]->index = swi1;
            backpack.backpack_pokemons[swi2]->index = swi2;
            
            sw = false;
            swi1 = -1;
            swi2 = -1;
        }
    }
}

#include "center.hpp"

Center::Center(){
    Selecteditem = 0;
    arrow = true;
    action_list = {"Heal", "Pokemon Box"};
    
    if (!font.loadFromFile(/* resourcePath() + */ "Fonts/sansation.ttf")) {
        std::cout<<"Problem"<<std::endl;
    }
}

void Center::draw(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer, BackpackMap &backpack){
    if (trainer.state == "Healing"){
        Moveup(event);
        Movedown(event);
        
        sf::FloatRect viewBounds = getViewBounds(view);
        
        sf::Text text[2];
        for (int i=0; i < 2; i++){
            text[i].setCharacterSize(10);
            text[i].setFillColor(sf::Color::Black);
            text[i].setFont(font);
            text[i].setPosition(4+ viewBounds.width/2 + viewBounds.left, viewBounds.top + 10*i + 4);
            text[i].setString(action_list[i]);
        }
        
        text[Selecteditem].setFillColor(sf::Color::Red);
        
        sf::RectangleShape rect(sf::Vector2f(viewBounds.width/2, viewBounds.height/3));
        rect.setFillColor(sf::Color::White);
        rect.setOutlineThickness(2);
        rect.setOutlineColor(sf::Color::Black);
        rect.setPosition(sf::Vector2f(viewBounds.left + viewBounds.width/2 -2, viewBounds.top + 2));
        window.draw(rect);
        
        for(int i=0; i < 2; i++){
            window.draw(text[i]);
        }
        heal_pokemons(backpack, event, trainer);
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
        if (Selecteditem + 1 <= 1) {
            Selecteditem++;
        }
        arrow = false;
    }
    else if (event.type == sf::Event::KeyReleased&&event.key.code == sf::Keyboard::Down){
        arrow = true;
    }
}

    
void Center::heal_pokemons(BackpackMap &backpack, sf::Event &event, Trainer &trainer) {
    if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::X&&Selecteditem == 0){
        for (unsigned int i = 0; i < 3; i++) {
            if(backpack.backpack_pokemons[i]){
                backpack.backpack_pokemons[i]->health = 100;
            }
        }
        trainer.state = "Stop";
    }
}

#include "center.hpp"

Center::Center(){
    Selecteditem = 0;
    arrow = true;
    action_list = {"Heal", "Switch Pokemon"};
    
    if (!font.loadFromFile(/* resourcePath() + */ "Fonts/sansation.ttf")) {
        std::cout<<"Problem"<<std::endl;
    }
}

void Center::draw(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer){
    if (trainer.state == "Healing"){
        Moveup(event);
        Movedown(event);
        sf::FloatRect viewBounds = getViewBounds(view);
        
        for (int i=0; i < 2; i++){
            action[i].setCharacterSize(10);
            action[i].setFillColor(sf::Color::Black);
            action[i].setFont(font);
            action[i].setPosition(4+ viewBounds.width/2 + viewBounds.left, viewBounds.top + 10*i + 4);
            action[i].setString(action_list[i]);
        }
        
        action[Selecteditem].setFillColor(sf::Color::Red);
        
        sf::RectangleShape rect(sf::Vector2f(viewBounds.width/2, viewBounds.height/3));
        rect.setFillColor(sf::Color::White);
        rect.setOutlineThickness(2);
        rect.setOutlineColor(sf::Color::Black);
        rect.setPosition(sf::Vector2f(viewBounds.left + viewBounds.width/2 -2, viewBounds.top + 2));
        window.draw(rect);
        
        for(int i=0; i < 2; i++){
            window.draw(action[i]);
        }
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
            action[Selecteditem].setFillColor(sf::Color::Black);
            Selecteditem--;
            action[Selecteditem].setFillColor(sf::Color::Red);
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
            action[Selecteditem].setFillColor(sf::Color::Black);
            Selecteditem++;
            action[Selecteditem].setFillColor(sf::Color::Red);
        }
        arrow = false;
    }
    else if (event.type == sf::Event::KeyReleased&&event.key.code == sf::Keyboard::Down){
        arrow = true;
    }
}

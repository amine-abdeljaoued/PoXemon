#include "shop.hpp"

template <typename T>
std::string toString(T arg){
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

Shop::Shop(){
    Selecteditem = 0;
    arrow = true;
    
    //All the items that can be purchased
    item_list = {"Normalball","Superball", "Masterball", "Incubator", "Starpowder", "SmallHealthPotion", "BigHealthPotion"};
    
    //Prices
    price["Normalball"] = 10;
    price["Superball"] = 20;
    price["Masterball"] = 50;
    price["Incubator"] = 100;
    price["Starpowder"] = 30;
    price["SmallHealthPotion"] = 40;
    price["BigHealthPotion"] = 70;
    
    //Load textures for button and font
    if (!button_texture.loadFromFile(/* resourcePath() + */ "Sprites/button.png")) {
        std::cout<<"Problem"<<std::endl;
    }
    button.setTexture(button_texture);
    
    if (!font.loadFromFile(/* resourcePath() + */ "Fonts/sansation.ttf")) {
        std::cout<<"Problem"<<std::endl;
    }
    
    if (!money_texture.loadFromFile(/* resourcePath() + */ "Sprites/money.png")) {
        std::cout<<"Problem"<<std::endl;
    }
    moneyI.setTexture(money_texture);
    
    money = 300;
};

sf::FloatRect Shop::getViewBounds(const sf::View &view)
{
        sf::FloatRect rt;
        rt.left = view.getCenter().x - view.getSize().x/2.f;
        rt.top  = view.getCenter().y - view.getSize().y/2.f;
        rt.width  = view.getSize().x;
        rt.height = view.getSize().y;
        return rt;
}

void Shop::Moveup(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Up&&arrow == true){
        if (Selecteditem - 1 >= 0) {
            item[Selecteditem].setFillColor(sf::Color::Black);
            Selecteditem--;
            item[Selecteditem].setFillColor(sf::Color::Red);
        }
        arrow = false;
    }
    else if (event.type == sf::Event::KeyReleased&&event.key.code == sf::Keyboard::Up){
        arrow = true;
    }
}

void Shop::Movedown(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Down&&arrow == true){
        if (Selecteditem + 1 <= 6) {
            item[Selecteditem].setFillColor(sf::Color::Black);
            Selecteditem++;
            item[Selecteditem].setFillColor(sf::Color::Red);
        }
        arrow = false;
    }
    else if (event.type == sf::Event::KeyReleased&&event.key.code == sf::Keyboard::Down){
        arrow = true;
    }
}

void Shop::draw_shop(sf::RenderWindow &window, sf::View &view, sf::Event &event){
    
    Moveup(event);
    Movedown(event);
    
    sf::FloatRect viewBounds = getViewBounds(view);
    
    for (int i=0; i < 7; i++){
        item[i].setCharacterSize(10);
        item[i].setFillColor(sf::Color::Black);
        item[i].setFont(font);
        item[i].setPosition(4+ viewBounds.width/2 + viewBounds.left, viewBounds.top + 10*i + 4);
        item[i].setString(item_list[i]);
    }
    
    item[Selecteditem].setFillColor(sf::Color::Red);
    
    sf::RectangleShape rect(sf::Vector2f(viewBounds.width/2, viewBounds.height/3));
    rect.setFillColor(sf::Color::White);
    rect.setOutlineThickness(2);
    rect.setOutlineColor(sf::Color::Black);
    rect.setPosition(sf::Vector2f(viewBounds.left + viewBounds.width/2 -2, viewBounds.top + 2));
    window.draw(rect);
    
    for(int i=0; i < 7; i++){
        window.draw(item[i]);
    }
}

void Shop::draw_money(sf::RenderWindow &window, sf::View &view, sf::Event &event){
    sf::FloatRect viewBounds = getViewBounds(view);
    sf::RectangleShape rect(sf::Vector2f(viewBounds.width/4, viewBounds.height/8));
    rect.setFillColor(sf::Color::White);
    rect.setOutlineThickness(2);
    rect.setOutlineColor(sf::Color::Black);
    rect.setPosition(sf::Vector2f(viewBounds.left + 2, viewBounds.top + 2));
    window.draw(rect);
    
    sf::Text moneyS;
    moneyS.setString(toString(money));
    moneyS.setFillColor(sf::Color::Black);
    moneyS.setCharacterSize(10);
    moneyS.setFont(font);
    moneyS.setPosition(viewBounds.left + 50, viewBounds.top + 2);
    
    moneyI.setScale(0.1, 0.1);
    moneyI.setPosition(viewBounds.left +2, viewBounds.top +2);
    
    window.draw(moneyI);
    
    window.draw(moneyS);
    
}


void Shop::draw(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer){
    if (trainer.state == "Shopping"){
        draw_shop(window, view, event);
        draw_money(window, view, event);
    }
}

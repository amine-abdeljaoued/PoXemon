#include "shop.hpp"

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
    
    release = true;
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

//Buy Function
void Shop::Buy(sf::Event &event, Trainer &trainer, BackpackMap &backpack) {
    if (event.type == sf::Event::KeyPressed&&event.key.code == sf::Keyboard::X&&release == true){
        if (trainer.state == "Shopping") {
            if (price[item_list[Selecteditem]]<=backpack.wallet) {
                backpack.inventory[item_type[Selecteditem]] += 1;
                backpack.wallet -= price[item_list[Selecteditem]];
            }
            release = false;
        }
    }
    
    //bool release to check if key D is release or not
    else if (event.type == sf::Event::KeyReleased&&event.key.code == sf::Keyboard::X){
        release = true;
    }
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

//Draw function for the shop: big white rectangle, columns for items and their prices
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
    
    for (int i=0; i < 7; i++){
        price_column[i].setCharacterSize(10);
        price_column[i].setFillColor(sf::Color::Black);
        price_column[i].setFont(font);
        price_column[i].setPosition(110+ viewBounds.width/2 + viewBounds.left, viewBounds.top + 10*i + 4);
        price_column[i].setString(toString(price[item_list[i]]));
    }
    
    price_column[Selecteditem].setFillColor(sf::Color::Red);
    
    sf::RectangleShape rect(sf::Vector2f(viewBounds.width/2, viewBounds.height/3));
    rect.setFillColor(sf::Color::White);
    rect.setOutlineThickness(2);
    rect.setOutlineColor(sf::Color::Black);
    rect.setPosition(sf::Vector2f(viewBounds.left + viewBounds.width/2 -2, viewBounds.top + 2));
    
    cout << viewBounds.top << endl;
    window.draw(rect);
    
    for(int i=0; i < 7; i++){
        window.draw(item[i]);
        window.draw(price_column[i]);
    }
}

//Draw function for the money in the shop: small white rectangle and current money in wallet
void Shop::draw_money(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer, BackpackMap &backpack){
    
    Buy(event, trainer, backpack);
    
    sf::FloatRect viewBounds = getViewBounds(view);
    sf::RectangleShape rect(sf::Vector2f(viewBounds.width/4, viewBounds.height/9));
    rect.setFillColor(sf::Color::White);
    rect.setOutlineThickness(2);
    rect.setOutlineColor(sf::Color::Black);
    rect.setPosition(sf::Vector2f(viewBounds.left + 2, viewBounds.top + 2));
    window.draw(rect);
    
    sf::Text moneyS;
    moneyS.setString(toString(backpack.wallet));
    moneyS.setFillColor(sf::Color::Black);
    moneyS.setCharacterSize(10);
    moneyS.setFont(font);
    moneyS.setPosition(viewBounds.left + 50, viewBounds.top + 5);
    
    moneyI.setScale(0.1, 0.1);
    moneyI.setPosition(viewBounds.left +5, viewBounds.top +5);
    
    window.draw(moneyI);
    
    window.draw(moneyS);
}

//Final function for drawing the shop
void Shop::draw(sf::RenderWindow &window, sf::View &view, sf::Event &event, Trainer &trainer, BackpackMap &backpack){
    if (trainer.state == "Shopping"){
        draw_shop(window, view, event);
        draw_money(window, view, event, trainer, backpack);
    }
}

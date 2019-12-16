#include "test.h"
#include "Backpack_content.h"
#include "ResourcePath.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>

template <typename T>
std::string toString(T arg){
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

Test::Test(float width, float height) {
    
    if (!font_menu.loadFromFile(/* resourcePath() + */ "Fonts/sansation.ttf")) {
        std::cout<<"Problem"<<std::endl;
    }
   
    menu[0].setFillColor(sf::Color::White);
    menu[0].setFont(font_menu);
    menu[0].setPosition(width/1.5, (height/8)*1);
    
    
    menu[1].setFillColor(sf::Color::Black);
    menu[1].setFont(font_menu);
    menu[1].setPosition(width/1.5, (height/8)*2);
    
    
    menu[2].setFillColor(sf::Color::Black);
    menu[2].setFont(font_menu);
    menu[2].setPosition(width/1.5, (height/8)*3);
    
    
    menu[3].setFillColor(sf::Color::Black);
    menu[3].setFont(font_menu);
    menu[3].setPosition(width/1.5, (height/8)*4);
    
    
    menu[4].setFillColor(sf::Color::Black);
    menu[4].setFont(font_menu);
    menu[4].setPosition(width/1.5, (height/8)*5);
    
    menu[5].setFillColor(sf::Color::Black);
    menu[5].setFont(font_menu);
    menu[5].setPosition(width/1.5, (height/8)*6);
    
    menu[6].setFillColor(sf::Color::Black);
    menu[6].setFont(font_menu);
    menu[6].setPosition(width/1.5, (height/8)*7);
    
    Selecteditem = 0;
}

void Test::drawing(sf::RenderTarget &target, Backpack back) {
    menu[0].setString("Pokeball                        x" + toString(back.inventory["Normalball"]));
    menu[1].setString("Superball                       x" + toString(back.inventory["Superball"]));
    menu[2].setString("Masterball                     x" + toString(back.inventory["Masterball"]));
    menu[3].setString("Incubator                       x" + toString(back.inventory["Incubator"]));
    menu[4].setString("Star Powder                  x" + toString(back.inventory["Starpowder"]));
    menu[5].setString("Small Health Potion    x" + toString(back.inventory["SmallHealthPotion"]));
    menu[6].setString("Big Health Potion        x" + toString(back.inventory["BigHealthPotion"]));
    for (int i = 0; i<7 ; i++) {
        target.draw(menu[i]);
    }
}

void Test::Moveup() {
    if (Selecteditem - 1 >= 0) {
        menu[Selecteditem].setFillColor(sf::Color::Black);
        Selecteditem--;
        menu[Selecteditem].setFillColor(sf::Color::White);
    }
}

void Test::Movedown() {
    if (Selecteditem + 1 <= 6) {
        menu[Selecteditem].setFillColor(sf::Color::Black);
        Selecteditem++;
        menu[Selecteditem].setFillColor(sf::Color::White);
    }
}

int Test::getPresseditem() {
    return Selecteditem;
}

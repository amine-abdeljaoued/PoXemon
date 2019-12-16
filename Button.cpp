#include "Button.h"
#include "Backpack_content.h"
#include "test.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include "ResourcePath.hpp"
#include "toString.h"

Button::Button() {
    
    //Load textures for button and font
    if (!button_texture.loadFromFile(resourcePath() + "button.png")) {
        return EXIT_FAILURE;
    }
    
    if (!font_menu.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    if (!money_texture.loadFromFile(resourcePath() + "money.png")) {
        return EXIT_FAILURE;
    }
    
    //Set texture and scale for button
    button.setTexture(button_texture);
    button.setScale(0.5, 0.5);
    
    //Set Color, size and font for the future text in the button
    title.setFont(font_menu);
    title.setCharacterSize(20);
    title.setFillColor(sf::Color::Black);
}

//If the button is the delete one, we apply this method to give it the delete appereance
void Button::Deletebutton(float width, float height) {
    button.setPosition(15, height - 60);
    title.setString("Delete");
    title.setPosition(50, height-47);
}

//If the button is the buying one, we apply this method to give it the buying appearence
void Button::Buyingbutton(float width, float height, Backpack back, Test menu) {
    button.setPosition(160, height - 60);
    title.setString("Buy  " + toString(back.cost[item_type[menu.Selecteditem]]));
    title.setPosition(150+28, height - 47);
    money.setTexture(money_texture);
    money.setScale(0.27, 0.27);
    money.setPosition(150+28+83, height - 54);
}

void Button::Money(Backpack back) {
    button.setPosition(15, 15);
    money_account.setString(toString(back.wallet));
    money_account.setFont(font_menu);
    money_account.setFillColor(sf::Color::Black);
    money_account.setCharacterSize(30);
    money_account.setPosition(35, 22);
    money.setTexture(money_texture);
    money.setScale(0.3, 0.3);
    money.setPosition(110, 20);
}

//Method that tells us if the mouse pointer is one the button or not
bool Button::isSpriteHover(sf::FloatRect sprite, sf::Vector2f mp) {
    if (sprite.contains(mp)){
        return true;
    }
    return false;
}

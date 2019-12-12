#pragma once
#include <SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
public:
    Menu();
    void draw (sf::RenderTarget &target) const;
//    void setPosition (sf::RenderTarget &target, float x, float y);
//    void MoveUp();
//    void MoveDown();
//    int GetPressedItem() { return selectedItemIndex; }

//private:
    //int selectedItemIndex;
    sf::Font font_menu;
    sf::Text menu;

};

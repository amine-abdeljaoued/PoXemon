#pragma once
#include <SFML/Graphics.hpp>
#include "Backpack_content.hpp"

class Test
{
public:
    Test(float width, float height);
    void drawing (sf::RenderTarget &target, Backpack back);
    void Moveup();
    void Movedown();
    int getPresseditem();
    Backpack back;
    int Selecteditem;
private:
    sf::Text menu[7];
    sf::Font font_menu;
};

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "test.h"
#include "Backpack_content.h"

class Button {
    
public:
    Button();
    bool isSpriteHover(sf::FloatRect button, sf::Vector2f mp);
    void Deletebutton(float width, float height);
    void Buyingbutton(float width, float height, Backpack back, Test menu);
    void Money(Backpack back);
    sf::Vector2f mp;
    sf::Sprite button;
    sf::Sprite money;
    sf::Text title;
    sf::Text money_account;
    Backpack back;
    Test menu(float width, float height);
    
private:
    sf::Texture button_texture;
    sf::Texture money_texture;
    sf::Font font_menu;
};

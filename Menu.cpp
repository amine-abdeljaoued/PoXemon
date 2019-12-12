#include "Menu.h"
#include "ResourcePath.hpp"


Menu::Menu()
{

    sf::Font font_menu;
    if (!font_menu.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }

    //int n = 2;
    
    menu.setFont(font_menu);
    menu.setFillColor(sf::Color::Red);
    menu.setString("Pokeball");
    //menu[0].setPosition(sf::Vector2f(width / 2, height / (n+ 1) * 1));

//    menu[1].setFont(font_menu);
//    menu[1].setFillColor(sf::Color::White);
//    menu[1].setString("Masterball");
//    //menu[1].setPosition(sf::Vector2f(width / 2, height / (n + 1) * 2));
//
//    menu[2].setFont(font_menu);
//    menu[2].setFillColor(sf::Color::White);
//    menu[2].setString("Hyperball");
//    //menu[2].setPosition(sf::Vector2f(width / 2, height / (n + 1) * 3));

    //selectedItemIndex = 0;
}


//Menu::~Menu()
//{
//}

//void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) {
////    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
////    {
//        menu.draw(sf::RenderTarget &target, sf::RenderStates::Default);
////    }
//}



//void Menu::draw (sf::RenderTarget &target) const {
//    target.draw(menu);
//}

//void Menu::setPosition(sf::RenderTarget &target, <#float x#>, <#float y#>);

//void Menu::MoveUp()
//{
//    if (selectedItemIndex - 1 >= 0)
//    {
//        menu[selectedItemIndex].setFillColor(sf::Color::White);
//        selectedItemIndex--;
//        menu[selectedItemIndex].setFillColor(sf::Color::Red);
//    }
//}
//
//void Menu::MoveDown()
//{
//    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
//    {
//        menu[selectedItemIndex].setFillColor(sf::Color::White);
//        selectedItemIndex++;
//        menu[selectedItemIndex].setFillColor(sf::Color::Red);
//    }
//}

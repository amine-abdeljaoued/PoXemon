#include "intro.hpp"
#include <iostream>
/* #include "ResourcePath.hpp" */
#include <SFML/Audio.hpp>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <string>
#include <ctime>

//This is the menu that appears at the beggining of the game
int menu(std::string picture) {
    sf::RenderWindow menu(sf::VideoMode(1400, 700), "PoXemon", sf::Style::Titlebar | sf::Style::Close);
    sf::View view(sf::Vector2f(272, 272), sf::Vector2f(544, 272));
    view.zoom(0.6f);
    menu.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/8, 0));
//    // Create the main window
//    sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
//    sf::RenderWindow menu(desktop, "PoXemon");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile("Sprites/icon.png")) {
        std::cout << "Error" << std::endl;
    }
    menu.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(/* resourcePath() + */ picture)) {
        std::cout << "Error" << std::endl;
    }
    sf::Sprite background;
    sf::Vector2u TextureSize;
    sf::Vector2u WindowSize;
    TextureSize = texture.getSize();
    WindowSize = menu.getSize();

    float ScaleX = (float) WindowSize.x / TextureSize.x;
    float ScaleY = (float) WindowSize.y / TextureSize.y;
    
    background.setTexture(texture);
    background.setScale(ScaleX, ScaleY);      //Set scale.
    
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(/* resourcePath() + */ "Fonts/sansation.ttf")) {
        std::cout << "Error" << std::endl;
    }
    sf::Text title("Start Game", font, 70);
    title.setStyle(sf::Text::Bold);
    title.setFillColor(sf::Color::Black);
    title.setPosition(WindowSize.x*(0.390), WindowSize.y*(0.65));
    
    // Create an explanation
    sf::Text expl("Press X to go forward", font, 30);
    expl.setStyle(sf::Text::Bold);
    expl.setFillColor(sf::Color::Black);
    expl.setPosition(WindowSize.x*(0.75), WindowSize.y*(0.90));

    // Start the game loop
    while (menu.isOpen())
    {
        // Process events
        sf::Event event;
        while (menu.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) return 10;
            // Advance button:
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::X)) menu.close();
            
            // Click start button:
            if (event.type == sf::Event::MouseButtonPressed)
            {
                float spot_x = title.getPosition().x;
                float spot_y = title.getPosition().y;
                float end_x = title.getPosition().x + WindowSize.x*(0.10);
                float end_y = title.getPosition().y + WindowSize.y*(0.05);
                
                if ( (event.mouseButton.button == sf::Mouse::Left) && (event.mouseButton.x > (spot_x-20)) && (event.mouseButton.x < (end_x+20)) && (event.mouseButton.y > (spot_y-20)) && (event.mouseButton.y < (end_y+20)) ) menu.close();
                }
            }
            menu.clear();
            menu.draw(background);
            menu.draw(title);
            menu.draw(expl);
            menu.display();
        }
    return 0;
}

int loadgame(std::string picture) {

    sf::RenderWindow menu(sf::VideoMode(1400, 700), "PoXemon", sf::Style::Titlebar | sf::Style::Close);
    sf::View view(sf::Vector2f(272, 272), sf::Vector2f(544, 272));
    view.zoom(0.6f);
    menu.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/8, 0));
//    // Create the main window
//    sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
//    sf::RenderWindow menu(desktop, "PoXemon");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile("Sprites/icon.png")) {
        std::cout << "Error" << std::endl;
    }
    menu.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(/* resourcePath() + */ picture)) {
        std::cout << "Error" << std::endl;
    }
    sf::Sprite background;
    sf::Vector2u TextureSize;
    sf::Vector2u WindowSize;
    TextureSize = texture.getSize();
    WindowSize = menu.getSize();

    float ScaleX = (float) WindowSize.x / TextureSize.x;
    float ScaleY = (float) WindowSize.y / TextureSize.y;
    
    background.setTexture(texture);
    background.setScale(ScaleX, ScaleY);      //Set scale.
    
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(/* resourcePath() + */ "Fonts/sansation.ttf")) {
        std::cout << "Error" << std::endl;
    }
    sf::Text title("New Game", font, 60);
    title.setStyle(sf::Text::Bold);
    title.setFillColor(sf::Color::Black);
    title.setPosition(WindowSize.x*(0.20), WindowSize.y*(0.60));
    sf::Text title2("Load Game", font, 60);
    title2.setStyle(sf::Text::Bold);
    title2.setFillColor(sf::Color::Black);
    title2.setPosition(WindowSize.x*(0.60), WindowSize.y*(0.60));
    
    // Create an explanation
    sf::Text expl("Click on your choice", font, 30);
    expl.setStyle(sf::Text::Bold);
    expl.setFillColor(sf::Color::Black);
    expl.setPosition(WindowSize.x*(0.75), WindowSize.y*(0.90));
    
    sf::Text expl2("Paste the load file path then press load game", font, 30);
    expl2.setStyle(sf::Text::Bold);
    expl2.setFillColor(sf::Color::Black);
    expl2.setPosition(WindowSize.x*(0.38), WindowSize.y*(0.85));
    
    sf::Text gamepath("", font, 40);
    gamepath.setStyle(sf::Text::Bold);
    gamepath.setFillColor(sf::Color::Black);
    gamepath.setPosition(WindowSize.x*(0.42), WindowSize.y*(0.76));
    
    sf::RectangleShape choice1(sf::Vector2f(400.f, 50.f));
    choice1.setOutlineThickness(10.f);
    choice1.setOutlineColor(sf::Color(1, 1, 1));
    choice1.setPosition(WindowSize.x*(0.4), WindowSize.y*(0.75));
    
    sf::String playerInput;
    sf::Text playerText;
    
    // Start the game loop
    while (menu.isOpen())
    {
        // Process events
        sf::Event event;

        
        
        while (menu.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) return 10;
            // Advance button:
//            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::X)) menu.close();
            
            // Click start button:
            if (event.type == sf::Event::MouseButtonPressed)
            {
                float spot_x = title.getPosition().x;
                float spot_y = title.getPosition().y;
                float end_x = title.getPosition().x + WindowSize.x*(0.10);
                float end_y = title.getPosition().y + WindowSize.y*(0.05);
                
                if ( (event.mouseButton.button == sf::Mouse::Left) && (event.mouseButton.x > (spot_x-20)) && (event.mouseButton.x < (end_x+20)) && (event.mouseButton.y > (spot_y-20)) && (event.mouseButton.y < (end_y+20)) ) {
                    time_t now = time(0);
                    char* dt = ctime(&now);
                    
                    std::ofstream myfile;
                    myfile.open ("save.txt");
                    myfile << "New game created on the "<< dt << std::endl;
                    myfile.close();
                    menu.close();
                }
                
                float spot2_x = title2.getPosition().x;
                float spot2_y = title2.getPosition().y;
                float end2_x = title2.getPosition().x + WindowSize.x*(0.10);
                float end2_y = title2.getPosition().y + WindowSize.y*(0.05);
                
                if ( (event.mouseButton.button == sf::Mouse::Left) && (event.mouseButton.x > (spot2_x-20)) && (event.mouseButton.x < (end2_x+20)) && (event.mouseButton.y > (spot2_y-20)) && (event.mouseButton.y < (end2_y+20)) ) {
    
                        std::ifstream    inFile(gamepath.getString());
                        std::ofstream    outFile("save.txt");

                        outFile << inFile.rdbuf();
                    return 9;
                    }
                }
            if (event.type == sf::Event::TextEntered){
                playerInput +=event.text.unicode;
                if (event.text.unicode == '\b' && playerInput.getSize()>1 ) playerInput.erase(playerInput.getSize() - 2, 2);
                gamepath.setString(playerInput);
                }
            }
            menu.clear();
            menu.draw(background);
            menu.draw(title);
            menu.draw(title2);
            menu.draw(expl);
            menu.draw(expl2);
            menu.draw(choice1);
            menu.draw(gamepath);
            menu.display();
        }
    return 0;
}

int intro(std::string picture, bool side, int which) {
    
    sf::RenderWindow intro(sf::VideoMode(1400, 700), "PoXemon", sf::Style::Titlebar | sf::Style::Close);
    sf::View view(sf::Vector2f(272, 272), sf::Vector2f(544, 272));
    view.zoom(0.6f);
    intro.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/8, 0));
    // Create the main window
//    sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
//    sf::RenderWindow intro(desktop, "PoXemon");
    
    sf::FloatRect rt;
//    sf::View view;
    rt.left = view.getCenter().x - view.getSize().x/2.f;
    rt.top  = view.getCenter().y - view.getSize().y/2.f;
    rt.width  = view.getSize().x;
    rt.height = view.getSize().y;

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(/* resourcePath() +  */"Sprites/icon.png")) {
        std::cout << "Error" << std::endl;
    }
    intro.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a background to display
    sf::Texture texture;
    if (!texture.loadFromFile(/* resourcePath() +  */"Sprites/menu_2.jpg")) {
        std::cout << "Error" << std::endl;
    }
    sf::Sprite background;
    sf::Vector2u TextureSize;
    sf::Vector2u WindowSize;
    TextureSize = texture.getSize();
    WindowSize = intro.getSize();

    float ScaleX = (float) WindowSize.x / TextureSize.x;
    float ScaleY = (float) WindowSize.y / TextureSize.y;
    
    background.setTexture(texture);
    background.setScale(ScaleX, ScaleY);      //Set scale.
    
    // Create an image to appear
       
    sf::Texture image;
    if (!image.loadFromFile(/* resourcePath() + */ picture)) {
        std::cout << "Error" << std::endl;
    }
    sf::Sprite professor;
    sf::Vector2u ImageSize;
    professor.scale(sf::Vector2f(1.f, 1.f)); //Set scale
    
    // Create a dialogue box
    sf::RectangleShape dialogue(sf::Vector2f(900.f, 200.f));
    dialogue.setOutlineThickness(5.f);
    dialogue.setOutlineColor(sf::Color(1, 1, 1));
    
    // Create a graphical text to display
    sf::Text title;
    sf::Font font;
    if (!font.loadFromFile(/* resourcePath() + */ "Fonts/sansation.ttf")) {
        std::cout << "Error" << std::endl;
    }
    title.setFont(font);
    title.setCharacterSize(50);
    title.setStyle(sf::Text::Bold);
    title.setFillColor(sf::Color::Black);
    
    // Create a second line of graphical text to display
    sf::Text subtitle;

    subtitle.setFont(font);
    subtitle.setCharacterSize(50);
    subtitle.setStyle(sf::Text::Bold);
    subtitle.setFillColor(sf::Color::Black);
    
    if (side == 0){
    professor.setPosition(rt.left + 0.15*rt.width, rt.top + 0.50*rt.height);
    professor.setTexture(image);
    dialogue.setPosition(rt.left + 1*rt.width, rt.top - 0.5*rt.height);
    title.setPosition(rt.left + 1*rt.width, rt.top - 0.4*rt.height);
    subtitle.setPosition(rt.left + 1.3*rt.width, rt.top + 0.2*rt.height);
    }
        
    if (side == 1){
    professor.setPosition(rt.left + 1.80*rt.width, rt.top + 0.50*rt.height);
    professor.setTexture(image);
    dialogue.setPosition(rt.left + 0.10*rt.width, rt.top - 0.5*rt.height);
    title.setPosition(rt.left - 0.12*rt.width, rt.top - 0.4*rt.height);
    subtitle.setPosition(rt.left + 0.23*rt.width, rt.top + 0.2*rt.height);
    }
    
    // Create an explanation
    sf::Text expl("Press X to go forward", font, 40);
    expl.setStyle(sf::Text::Bold);
    expl.setFillColor(sf::Color::Black);
    if (side == 1){
        expl.setPosition(WindowSize.x*(0.15), WindowSize.y*(0.90));
    }
    if (side == 0){
        expl.setPosition(WindowSize.x*(0.70), WindowSize.y*(0.90));
    }
    
    if (which == 0){
    std::string str = "Hi! Sorry to keep you waiting!";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 1){
    std::string str = "Welcome to the world of PoXemon!";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 2){
    std::string str = "My name is Didy.";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 3){
    std::string str = "But everyone calls me Professor PoXemon.";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 4){
    std::string str = "The campus is widely inhabited by creatures";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    std::string str_2 = "called PoXemon.";
        while (str_2.length() < 40){
            str_2 = " " + str_2;
        }
    subtitle.setString(str_2);
    }
    
    if (which == 5){
    std::string str = "We humans live alongside PoXemon,";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 6){
    std::string str = "at times as friendly playmates,";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    std::string str_2 = "and at times as cooperative workmates.";
        while (str_2.length() < 40){
            str_2 = " " + str_2;
        }
    subtitle.setString(str_2);
    }
    
    if (which == 7){
    std::string str = "And sometimes, we band together";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    std::string str_2 = "and battle others like us.";
        while (str_2.length() < 40){
            str_2 = " " + str_2;
        }
    subtitle.setString(str_2);
    }
    
    if (which == 8){
    std::string str = "But despite our closeness,";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    std::string str_2 = "we don't know everything about PoXemon.";
        while (str_2.length() < 40){
            str_2 = " " + str_2;
        }
    subtitle.setString(str_2);
    }

    if (which == 9){
    std::string str = "In fact, there are many,";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 10){
    std::string str = "many secrets surrounding PoXemon.";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 11){
    std::string str = "To unravel PoXemon mysteries,";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    std::string str_2 = "I've been undertaking research.";
        while (str_2.length() < 40){
            str_2 = " " + str_2;
        }
    subtitle.setString(str_2);
    }
    
    if (which == 12){
    std::string str = "That's what I do.";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 15){
    std::string str = "This is a shame. Have a nice journey home.";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    }
    
    if (which == 16){
    std::string str = "You have to accept your PoXemon";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
        std::string str_2 = "with love and respect.";
            while (str_2.length() < 40){
                str_2 = " " + str_2;
            }
        subtitle.setString(str_2);
    }
    
    if (which == 17){
    std::string str = "For that, I'll have you choose";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
        std::string str_2 = "one of my three precious PoXemon.";
            while (str_2.length() < 40){
                str_2 = " " + str_2;
            }
        subtitle.setString(str_2);
    }
    
    if (which == 18){
    std::string str = "Excellent! Raporoy won't let you down";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
        std::string str_2 = "You are now ready to start!";
            while (str_2.length() < 40){
                str_2 = " " + str_2;
            }
        subtitle.setString(str_2);
    }
    
    if (which == 19){
    std::string str = "Excellent! Wapefet won't let you down";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
        std::string str_2 = "You are now ready to start!";
            while (str_2.length() < 40){
                str_2 = " " + str_2;
            }
        subtitle.setString(str_2);
    }
    
    if (which == 20){
    std::string str = "Excellent! Gangstakabra won't let you down";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
        std::string str_2 = "You are now ready to start!";
            while (str_2.length() < 40){
                str_2 = " " + str_2;
            }
        subtitle.setString(str_2);
    }
    
    
    // Start the game loop
    while (intro.isOpen())
    {
        // Process events
        sf::Event event;
        while (intro.pollEvent(event)) {
            
            if (event.type == sf::Event::Closed) return 10;
            
            // Advance button:
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::X) intro.close();
            
        intro.clear();
        intro.draw(background);
        intro.draw(professor);
        intro.draw(dialogue);
        intro.draw(title);
        intro.draw(subtitle);
            if (which < 2){
                intro.draw(expl);
            }
        intro.display();
}
}
    return 9;
}

bool choice(std::string prof, bool side, int which) {
    
    sf::RenderWindow choice(sf::VideoMode(1400, 700), "PoXemon", sf::Style::Titlebar | sf::Style::Close);
    sf::View view(sf::Vector2f(272, 272), sf::Vector2f(544, 272));
    view.zoom(0.6f);
    choice.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/8, 0));
//    // Create the main window
//    sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
//    sf::RenderWindow choice(desktop, "PoXemon");
    
    sf::FloatRect rt;
//    sf::View view;
    rt.left = view.getCenter().x - view.getSize().x/2.f;
    rt.top  = view.getCenter().y - view.getSize().y/2.f;
    rt.width  = view.getSize().x;
    rt.height = view.getSize().y;

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(/* resourcePath() + */ "Sprites/icon.png")) {
        std::cout << "Error" << std::endl;
    }
    choice.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a background to display
    
    sf::Texture texture;
    if (!texture.loadFromFile(/* resourcePath() + */ "Sprites/menu_2.jpg")) {
        std::cout << "Error" << std::endl;
    }
    sf::Sprite background;
    sf::Vector2u TextureSize;
    sf::Vector2u WindowSize;
    TextureSize = texture.getSize();
    WindowSize = choice.getSize();

    float ScaleX = (float) WindowSize.x / TextureSize.x;
    float ScaleY = (float) WindowSize.y / TextureSize.y;
    
    background.setTexture(texture);
    background.setScale(ScaleX, ScaleY);      //Set scale.
    
    // Create an image to appear
       
    sf::Texture image;
    if (!image.loadFromFile(/* resourcePath() + */ prof)) {
        std::cout << "Error" << std::endl;
    }
    sf::Sprite professor;
    sf::Vector2u ImageSize;
    professor.scale(sf::Vector2f(1.f, 1.f)); //Set scale
    
    // Create a dialogue box
    sf::RectangleShape dialogue(sf::Vector2f(900.f, 200.f));
    dialogue.setOutlineThickness(5.f);
    dialogue.setOutlineColor(sf::Color(1, 1, 1));
    
    // Create a choice 1
    sf::RectangleShape choice1(sf::Vector2f(400.f, 100.f));
    choice1.setOutlineThickness(2.f);
    choice1.setOutlineColor(sf::Color(1, 1, 1));
    
    // Create a choice 2
    sf::RectangleShape choice2(sf::Vector2f(400.f, 100.f));
    choice2.setOutlineThickness(2.f);
    choice2.setOutlineColor(sf::Color(1, 1, 1));
    
    // Create a graphical text to display
    sf::Text title;
    sf::Font font;
    if (!font.loadFromFile(/* resourcePath() + */ "Fonts/sansation.ttf")) {
        std::cout << "Error" << std::endl;
    }
    title.setFont(font);
    title.setCharacterSize(50);
    title.setStyle(sf::Text::Bold);
    title.setFillColor(sf::Color::Black);
    
    // Create a second line of graphical text to display
    sf::Text subtitle;

    subtitle.setFont(font);
    subtitle.setCharacterSize(50);
    subtitle.setStyle(sf::Text::Bold);
    subtitle.setFillColor(sf::Color::Black);
    
    // Create a first option
    sf::Text option1;

    option1.setFont(font);
    option1.setCharacterSize(40);
    option1.setStyle(sf::Text::Bold);
    option1.setFillColor(sf::Color::Black);
    
    // Create a second option
    sf::Text option2;

    option2.setFont(font);
    option2.setCharacterSize(40);
    option2.setStyle(sf::Text::Bold);
    option2.setFillColor(sf::Color::Black);
    
    if (side == 0){
    professor.setPosition(rt.left + 0.15*rt.width, rt.top + 0.50*rt.height);
    professor.setTexture(image);
        
    dialogue.setPosition(rt.left + 1*rt.width, rt.top - 0.5*rt.height);
    title.setPosition(rt.left + 1*rt.width, rt.top - 0.4*rt.height);
    subtitle.setPosition(rt.left + 1.3*rt.width, rt.top + 0.2*rt.height);
    choice1.setPosition(rt.left + 1.40*rt.width, rt.top + 0.80*rt.height);
    choice2.setPosition(rt.left + 2.10*rt.width, rt.top + 0.80*rt.height);
    option1.setPosition(rt.left + 1.00*rt.width, rt.top + 0.83*rt.height);
    option2.setPosition(rt.left + 1.90*rt.width, rt.top + 0.83*rt.height);
    }
        
    if (side == 1){
    professor.setPosition(rt.left + 1.80*rt.width, rt.top + 0.50*rt.height);
    professor.setTexture(image);
        
    dialogue.setPosition(rt.left + 0.10*rt.width, rt.top - 0.5*rt.height);
    title.setPosition(rt.left - 0.12*rt.width, rt.top - 0.4*rt.height);
    subtitle.setPosition(rt.left + 0.23*rt.width, rt.top + 0.2*rt.height);
    choice1.setPosition(rt.left + 0.20*rt.width, rt.top + 0.80*rt.height);
    choice2.setPosition(rt.left + 0.90*rt.width, rt.top + 0.80*rt.height);
    option1.setPosition(rt.left - 0.20*rt.width, rt.top + 0.83*rt.height);
    option2.setPosition(rt.left + 0.50*rt.width, rt.top + 0.83*rt.height);
    }
    
    // Create an explanation
    sf::Text expl("Press the left arrow for left choice, right arrow for the right choice", font, 40);
    expl.setStyle(sf::Text::Bold);
    expl.setFillColor(sf::Color::Black);
    if (side == 1){
        expl.setPosition(WindowSize.x*(0.15), WindowSize.y*(0.90));
    }
    if (side == 0){
        expl.setPosition(WindowSize.x*(0.70), WindowSize.y*(0.90));
    }
    
    if (which == 13){
    std::string str = "And you?";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    std::string str_2 = "What is your name?";
        while (str_2.length() < 40){
            str_2 = " " + str_2;
        }
    subtitle.setString(str_2);
    std::string str_3 = "Boy";
        while (str_3.length() < 40){
            str_3 = " " + str_3;
        }
    option1.setString(str_3);
    std::string str_4 = "Girl";
        while (str_4.length() < 40){
            str_4 = " " + str_4;
        }
    option2.setString(str_4);
    }
    
    if (which == 14){
    std::string str = "And tell me, my friend,";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    std::string str_2 = "do you like PoXemon?";
        while (str_2.length() < 40){
            str_2 = " " + str_2;
        }
    subtitle.setString(str_2);
    std::string str_3 = "Yes";
        while (str_3.length() < 40){
            str_3 = " " + str_3;
        }
    option1.setString(str_3);
    std::string str_4 = "No";
        while (str_4.length() < 40){
            str_4 = " " + str_4;
        }
    option2.setString(str_4);
    }
    
    
    // Start the game loop
    while (choice.isOpen())
    {
        // Process events
        sf::Event event;
        while (choice.pollEvent(event)) {
            if (event.type == sf::Event::Closed) return 10;
            // Click button 1:
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                if (which==13){
                    std::fstream myfile;
                    std::string line, someString;
                    myfile.open("save.txt");
                    while (!myfile.eof())
                    {
                        std::getline(myfile,line); // Check getline() doc, you can retrieve a line before/after a given string etc.
                        myfile << "boy" << std::endl;
                    }
                    myfile.close();
                }
                    choice.close();
                    return 0;
                }
                
            // Click button 2:
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                if (which==13){
                    std::fstream myfile;
                    std::string line, someString;
                    myfile.open("save.txt");
                    while (!myfile.eof())
                    {
                        std::getline(myfile,line); // Check getline() doc, you can retrieve a line before/after a given string etc.
                        myfile << "girl" << std::endl;
                    }
                    myfile.close();
                }
                    choice.close();
                    return 1;
                }
            
        choice.clear();
        choice.draw(background);
        choice.draw(professor);
        choice.draw(dialogue);
        choice.draw(choice1);
        choice.draw(choice2);
        choice.draw(title);
        choice.draw(subtitle);
        choice.draw(option1);
        choice.draw(option2);
        choice.draw(expl);
        choice.display();
}
}
    return 0;
}


int choose(std::string prof, bool side) {
    
    sf::RenderWindow choose(sf::VideoMode(1400, 700), "PoXemon", sf::Style::Titlebar | sf::Style::Close);
    sf::View view(sf::Vector2f(272, 272), sf::Vector2f(544, 272));
    view.zoom(0.6f);
    choose.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/8, 0));
//    // Create the main window
//    sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
//    sf::RenderWindow choose(desktop, "PoXemon");
    
    sf::FloatRect rt;
//    sf::View view;
    rt.left = view.getCenter().x - view.getSize().x/2.f;
    rt.top  = view.getCenter().y - view.getSize().y/2.f;
    rt.width  = view.getSize().x;
    rt.height = view.getSize().y;

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(/* resourcePath() + */ "Sprites/icon.png")) {
        std::cout << "Error" << std::endl;
    }
    choose.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a background to display
    sf::Texture texture;
    if (!texture.loadFromFile(/* resourcePath() +  */"Sprites/menu_3.png")) {
        std::cout << "Error" << std::endl;
    }
    sf::Sprite background;
    sf::Vector2u TextureSize;
    sf::Vector2u WindowSize;
    TextureSize = texture.getSize();
    WindowSize = choose.getSize();

    float ScaleX = (float) WindowSize.x / TextureSize.x;
    float ScaleY = (float) WindowSize.y / TextureSize.y;
    
    background.setTexture(texture);
    background.setScale(ScaleX, ScaleY);      //Set scale.
    
    // Create an image to appear
    sf::Texture image;
    if (!image.loadFromFile(/* resourcePath() + */ prof)) {
        std::cout << "Error" << std::endl;
    }
    sf::Sprite professor;
    sf::Vector2u ImageSize;
    professor.scale(sf::Vector2f(1.f, 1.f)); //Set scale
    
    // Create a dialogue box
    sf::RectangleShape dialogue(sf::Vector2f(900.f, 200.f));
    dialogue.setOutlineThickness(5.f);
    dialogue.setOutlineColor(sf::Color(1, 1, 1));
    
    // Create a choice 1
    sf::RectangleShape choice1(sf::Vector2f(400.f, 200.f));
    choice1.setOutlineThickness(2.f);
    choice1.setOutlineColor(sf::Color(1, 1, 1));
    
    // Create a choice 2
    sf::RectangleShape choice2(sf::Vector2f(400.f, 200.f));
    choice2.setOutlineThickness(2.f);
    choice2.setOutlineColor(sf::Color(1, 1, 1));
    
    // Create a choice 3
    sf::RectangleShape choice3(sf::Vector2f(400.f, 200.f));
    choice3.setOutlineThickness(2.f);
    choice3.setOutlineColor(sf::Color(1, 1, 1));
    
    // Create a graphical text to display
    sf::Text title;
    sf::Font font;
    if (!font.loadFromFile(/* resourcePath() + */ "Fonts/sansation.ttf")) {
        std::cout << "Error" << std::endl;
    }
    title.setFont(font);
    title.setCharacterSize(50);
    title.setStyle(sf::Text::Bold);
    title.setFillColor(sf::Color::Black);
    
    // Create a second line of graphical text to display
    sf::Text subtitle;

    subtitle.setFont(font);
    subtitle.setCharacterSize(50);
    subtitle.setStyle(sf::Text::Bold);
    subtitle.setFillColor(sf::Color::Black);
    
    // Create a first option
    sf::Text option1;

    option1.setFont(font);
    option1.setCharacterSize(30);
    option1.setStyle(sf::Text::Bold);
    option1.setFillColor(sf::Color::Black);
    
    // Create a second option
    sf::Text option2;

    option2.setFont(font);
    option2.setCharacterSize(30);
    option2.setStyle(sf::Text::Bold);
    option2.setFillColor(sf::Color::Black);
    
    // Create a third option
    sf::Text option3;

    option3.setFont(font);
    option3.setCharacterSize(30);
    option3.setStyle(sf::Text::Bold);
    option3.setFillColor(sf::Color::Black);

    professor.setPosition(rt.left + 1.80*rt.width, rt.top + 0.50*rt.height);
    professor.setTexture(image);
    dialogue.setPosition(rt.left + 0.10*rt.width, rt.top - 0.5*rt.height);
    title.setPosition(rt.left - 0.12*rt.width, rt.top - 0.4*rt.height);
    subtitle.setPosition(rt.left + 0.23*rt.width, rt.top + 0.2*rt.height);
    choice1.setPosition(rt.left + 0.20*rt.width, rt.top + 1.10*rt.height);
    choice2.setPosition(rt.left + 0.80*rt.width, rt.top + 1.10*rt.height);
    choice3.setPosition(rt.left + 1.40*rt.width, rt.top + 1.10*rt.height);
    option1.setPosition(rt.left + 0.00*rt.width, rt.top + 1.13*rt.height);
    option2.setPosition(rt.left + 0.60*rt.width, rt.top + 1.13*rt.height);
    option3.setPosition(rt.left + 1.20*rt.width, rt.top + 1.13*rt.height);
    
    // Create an explanation
    sf::Text expl("Press the left arrow for left choice, down arrow for the middle choice, right arrow for the right choice", font, 30);
    expl.setStyle(sf::Text::Bold);
    expl.setFillColor(sf::Color::Black);
    if (side == 1){
        expl.setPosition(WindowSize.x*(0.15), WindowSize.y*(0.90));
    }
    if (side == 0){
        expl.setPosition(WindowSize.x*(0.70), WindowSize.y*(0.90));
    }
    
    std::string str = "Which PoXemon";
        while (str.length() < 40){
            str = " " + str;
        }
    title.setString(str);
    std::string str_2 = "would you like to start with?";
        while (str_2.length() < 40){
            str_2 = " " + str_2;
        }
    subtitle.setString(str_2);
    std::string str_3 = "Raporoy"; // rouge
        while (str_3.length() < 30){
            str_3 = " " + str_3;
        }
    option1.setString(str_3);
    std::string str_4 = "Wapefet"; // bleu
        while (str_4.length() < 30){
            str_4 = " " + str_4;
        }
    option2.setString(str_4);
    std::string str_5 = "Gangstakabra"; // brown
        while (str_5.length() < 30){
            str_5 = " " + str_5;
        }
    option3.setString(str_5);
    
    
    // Start the game loop
    while (choose.isOpen())
    {
        // Process events
        sf::Event event;
        while (choose.pollEvent(event)) {
            if (event.type == sf::Event::Closed) return 10;
            // Click button 1:
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                    std::fstream myfile;
                    std::string line, someString;
                    myfile.open("save.txt");
                    while (!myfile.eof())
                    {
                        std::getline(myfile,line); // Check getline() doc, you can retrieve a line before/after a given string etc.
                        myfile << "raporoy" << std::endl;
                    }
                    myfile.close();
                    choose.close();
                    return -1;
                }
            
            // Click button 2:
            if (event.type == sf::Event::KeyPressed  && event.key.code == sf::Keyboard::Down) {
                    std::fstream myfile;
                    std::string line, someString;
                    myfile.open("save.txt");
                    while (!myfile.eof())
                    {
                        std::getline(myfile,line); // Check getline() doc, you can retrieve a line before/after a given string etc.
                        myfile << "wapefet" << std::endl;
                    }
                    myfile.close();
                    choose.close();
                    return -2;
                }
                
            // Click button 3:
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right){
                    std::fstream myfile;
                    std::string line, someString;
                    myfile.open("save.txt");
                    while (!myfile.eof())
                    {
                        std::getline(myfile,line); // Check getline() doc, you can retrieve a line before/after a given string etc.
                        myfile << "gangstakabra" << std::endl;
                    }
                    myfile.close();
                    choose.close();
                    return -3;
                }
            
        choose.clear();
        choose.draw(background);
        choose.draw(professor);
        choose.draw(dialogue);
        choose.draw(choice1);
        choose.draw(choice2);
        choose.draw(choice3);
        choose.draw(title);
        choose.draw(subtitle);
        choose.draw(option1);
        choose.draw(option2);
        choose.draw(option3);
        choose.draw(expl);
        choose.display();
}
}
    return 9;
}

int startgame(){
    int poke_name;
    sf::Music music;
    if (!music.openFromFile("Sprites/bgm02.ogg"))
        std::cout << "Error loading music" << std::endl;
    music.play();
    sf::Event event;
    int closed=0;
    closed = menu("Sprites/main_menu.jpg");
    if (closed<10) closed = loadgame("Sprites/main_menu.jpg");
    if (closed==9) return 0;
    if (closed<10)closed = intro("Sprites/professor1.png",1,0);
    if (closed<10)closed = intro("Sprites/professor4.png",1,1);
    if (closed<10)closed = intro("Sprites/professor3.png",0,2);
    if (closed<10)closed = intro("Sprites/professor5.png",0,3);
    if (closed<10)closed = intro("Sprites/professor2.png",0,4);
    if (closed<10)closed = intro("Sprites/professor6.png",1,5);
    if (closed<10)closed = intro("Sprites/professor7.png",1,6);
    if (closed<10)closed = intro("Sprites/professor1.png",0,7);
    if (closed<10)closed = intro("Sprites/professor4.png",0,8);
    if (closed<10)closed = intro("Sprites/professor6.png",1,9);
    if (closed<10)closed = intro("Sprites/professor5.png",1,10);
    if (closed<10)closed = intro("Sprites/professor3.png",0,11);
    if (closed<10)closed = intro("Sprites/professor2.png",0,12);
    if (closed<10)closed = choice("Sprites/professor1.png",1,13);
    if (closed<10){
        if(choice("Sprites/professor4.png",1,14)==1) {
            if(closed<10)closed=intro("Sprites/professor7.png",0,15);
            return 1;
        }
        else{
          if (closed<10)closed = intro("Sprites/professor4.png",0,16);
          if (closed<10)closed = intro("Sprites/professor1.png",1,17);
            if (closed<10) {
                poke_name = choose("Sprites/professor6.png",1);
                closed= poke_name;
            }
          if(closed==-1) closed = intro("Sprites/professor5.png",0,18);
          else if(closed==-2) closed = intro("Sprites/professor5.png",0,19);
          else if(closed==-3) closed = intro("Sprites/professor5.png",0,20);
        }
    }
    if (closed<10) return poke_name;
    else return 1;
}

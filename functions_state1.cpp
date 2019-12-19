#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

void initialise_background(sf::RenderWindow& window, std::string path, sf::Sprite& background, sf::Texture& texture){
	// Function that sets up our background to be the same size as the window
	// Need to initialise the sprite and texture of the background before though
	sf::Vector2u TextureSize;  //Added to store texture size.
	sf::Vector2u WindowSize;   //Added to store window size.

	if(!texture.loadFromFile(path)){std::cout<<"Background didn't load"<<std::endl;}
	else
	{
		TextureSize = texture.getSize(); 	//Get size of texture.
		WindowSize = window.getSize();      //Get size of window.

		float ScaleX = (float) WindowSize.x / TextureSize.x;
		float ScaleY = (float) WindowSize.y / TextureSize.y;     //Calculate scale.

		background.setTexture(texture);
		background.setScale(ScaleX, ScaleY);      //Set scale.  
  	}
}

void initialise_buttons(sf::RectangleShape& start_button, sf::RectangleShape& info_button, sf::RenderWindow& window, sf::Font& font, sf::Text& start_text,
                            sf::Text& info_text, sf::Text& intro_text, sf::Sprite& opp, sf::Sprite& star, sf::Texture& star_texture){
    // Rectangles
    start_button.setFillColor(sf::Color::White);
    info_button.setFillColor(sf::Color::White);
    start_button.setOutlineThickness(4);
    info_button.setOutlineThickness(4);
    start_button.setOutlineColor(sf::Color::Black);
    info_button.setOutlineColor(sf::Color::Black);
    start_button.setSize(sf::Vector2f(225,100));
    info_button.setSize(sf::Vector2f(225,100));

    //Sprites
    if (!star_texture.loadFromFile("Images/12star.png")){ std::cout << "could not load" << std::endl;}
    star_texture.loadFromFile("Images/12star.png");
    star.setTexture(star_texture);
    star.setScale(sf::Vector2f(0.75, 0.75));
    opp.setScale(sf::Vector2f(1,1));
    opp.setOrigin(0,0);

    // Text 
    std::string start = "Start";
    std::string info = "How to Play";
    
	start_text.setFont(font);
    info_text.setFont(font);
    intro_text.setFont(font);
	start_text.setCharacterSize(30);
    info_text.setCharacterSize(30);
    intro_text.setCharacterSize(60);
    start_text.setFillColor(sf::Color::Black);
    info_text.setFillColor(sf::Color::Black);
    intro_text.setFillColor(sf::Color::Black);
    intro_text.setOrigin(intro_text.getGlobalBounds().width/2, intro_text.getGlobalBounds().height); 
    start_text.setString(start);
    info_text.setString(info);

    // Setting the position:
    // First three variables are just ones that work nicely - but changing them is easy and will change the rest
    // Alignment is very dodgy
    int xoffset = 150;
    int yoffset = 75;
    int global_yoffset = 30;
    float x = window.getSize().x /2;
    float y = window.getSize().y /2;

    intro_text.setPosition(x,y-3*yoffset);
    start_button.setPosition(x-xoffset, y-yoffset+global_yoffset);
    info_button.setPosition(x-xoffset, y+yoffset+global_yoffset);
    start_text.setPosition(x-xoffset, y-yoffset+global_yoffset);
    info_text.setPosition(info_button.getPosition().x, info_button.getPosition().y);
    star.setPosition(x+xoffset,y+global_yoffset);
    opp.setPosition(x+xoffset,y+global_yoffset);

    // move is to get alignment
    start_button.move(-start_button.getGlobalBounds().width/2, -start_button.getGlobalBounds().height/2);
    start_text.move(-start_text.getGlobalBounds().width/2, -start_text.getGlobalBounds().height/2);
    info_text.move(-info_text.getGlobalBounds().width/2, -info_text.getGlobalBounds().height/2);
    info_button.move(-info_button.getGlobalBounds().width/2, -info_button.getGlobalBounds().height/2);
    star.move(-star.getGlobalBounds().width/2, -star.getGlobalBounds().height/2);
    opp.move(-opp.getGlobalBounds().width/2, -opp.getGlobalBounds().height/2);

    
    /* star.move(-star.getGlobalBounds().width/2, -star.getGlobalBounds().height/2);
    opp.move(-opp.getGlobalBounds().width/2, -opp.getGlobalBounds().height/2); */

}

void draw1(sf::RenderWindow& window, sf::RectangleShape& shape1, sf::RectangleShape& shape2, sf::Text& text1, sf::Text& text2,
            sf::Text& text3, sf::Sprite& sprite, sf::Sprite& bg ){
                window.draw(shape1);
                window.draw(shape2);
                window.draw(text1);
                window.draw(text2);
                window.draw(text3);
                window.draw(bg);
                window.draw(sprite);
            }

int update_state1(sf::RenderWindow& window, sf::RectangleShape& start_button, sf::RectangleShape& info_button, sf::Sprite& star){
    // Want to rotate the star: need it to have its origin at its centre
    // star.rotate(30);

    // Know where the mouse is
    // Buttons go red when hovering
    if ((sf::Event::MouseMoved)||(sf::Event::MouseButtonPressed)){
        sf::Vector2i mousepixel = sf::Mouse::getPosition(window);
        sf::Vector2f mouse_pos = window.mapPixelToCoords(mousepixel);
        if (start_button.getGlobalBounds().contains(mouse_pos)){
            start_button.setFillColor(sf::Color(255,99,99)); //reddish
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                return 2;
            }
        }
        else {
            start_button.setFillColor(sf::Color::White);
        }
        if (info_button.getGlobalBounds().contains(mouse_pos)){
            info_button.setFillColor(sf::Color(255,99,99));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                return 2;
            }
        }
        else {
            info_button.setFillColor(sf::Color::White);
        }
        return 1;
    }
}
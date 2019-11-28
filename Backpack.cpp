#include "Backpack.h"
#include<map>
#include<string>

Backpack::Backpack(){
    dict_pokeball["Normalball"] = 3;
    dict_pokeball["Superball"] = 3;
    dict_pokeball["Masterball"] = 3;
    
    //Outline with white base
    clickbox.setFillColor(sf::Color::White);
    clickbox.setOutlineThickness(4);
    clickbox.setOutlineColor(sf::Color::Black);
    clickbox.setSize(sf::Vector2f(100,40));
    clickbox.setPosition(50,100);
    
    normaltext.loadFromFile("Images/pokeball.png");
    normalball.setTexture(normaltext);
    normalball.setScale(sf::Vector2f(0.2f, 0.2f));
    normalball.setPosition(10,105);
    
    }
    void Backpack::Pokeball_shoot(float& deltaTime, sf::RenderWindow& window){
        
        
        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&(dict_pokeball["Normalball"]>0)&&new_Pokeball.in_air ==false){
            
                    //Get the mouse position:
                    sf::Vector2i mousepixel = sf::Mouse::getPosition(window);
                    sf::Vector2f mouse_pos = window.mapPixelToCoords(mousepixel);
                    //std::cout<<mouse_pos.x<<'\n';
                    //std::cout<<mouse_pos.y<<'\n';
            
            
            if((mouse_pos.x>50)&&(mouse_pos.x<150)&&(mouse_pos.y>100)&&(mouse_pos.y<140)){
                
                    
                    dict_pokeball["Normalball"]-=1;
                    std::cout<<dict_pokeball["Normalball"]<<'\n';
                    sf::Vector2u size = window.getSize();
                    float w = size.x;
                    float width = (float) w;
                    float h = size.y;
                    float height = (float) h + 2.0f;
                    float width4 = width/4;


                    new_Pokeball.setPosition(width4, height);// Need to figure out where the starting x and y position are
                    new_Pokeball.velocityY = -sqrt(5.0f * 981.0f * new_Pokeball.ballHeight); //We need to reset the ball's position and starting speed when you shoot, that's why its in this class
                    new_Pokeball.in_air = true;
            }
            
        }
                    //Continuation of the one shot as time goes by
                    if (new_Pokeball.in_air) {
                        bool still_on_screen = new_Pokeball.update(deltaTime, window);
                        //if the ball reached the end of the window, then the ball is not in air
                        if (!still_on_screen) {
                            new_Pokeball.in_air = false;

                        }
                    }
    }
    
    void Backpack::draw (sf::RenderTarget &target) const {
        if(new_Pokeball.in_air){
            target.draw(new_Pokeball.ball);
        }
        target.draw(clickbox);
        target.draw(normalball);
}

//function that updates the backpack containt
//void Backpack::update(){
//    if (ball_nbre>0){
//        if((ball.shooting == false)&&(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))){
//
//            ball_nbre-=1;
//        std::cout<<ball_nbre<<std::endl;
//        }
//    }
//}

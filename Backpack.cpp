#include "Backpack.h"
#include<map>
#include<string>

Backpack::Backpack(){
    dict_pokeball["Normalball"] = 3;
    dict_pokeball["Superball"] = 3;
    dict_pokeball["Masterball"] = 3;
    
    bool masternow = true;
    bool supernow = true;
    bool normalnow = true;
    
// //creates a box with nothing inside
//    //Outline with white base
//    clickbox.setFillColor(sf::Color::White);
//    clickbox.setOutlineThickness(4);
//    clickbox.setOutlineColor(sf::Color::Black);
//    clickbox.setSize(sf::Vector2f(100,40));
//    clickbox.setPosition(50,100);
    
    normaltext1.loadFromFile("Images/pokeball.png");
    normalball.setTexture(normaltext1);
    normalball.setScale(sf::Vector2f(0.2f, 0.2f));
    normalball.setPosition(20,150);
    
    normaltext2.loadFromFile("Images/superball.png");
    superball.setTexture(normaltext2);
    superball.setScale(sf::Vector2f(0.2f, 0.2f));
    superball.setPosition(70,150);

    normaltext3.loadFromFile("Images/masterball.png");
    masterball.setTexture(normaltext3);
    masterball.setScale(sf::Vector2f(0.055f, 0.055f));
    masterball.setPosition(120,150);
    
    new_Superball.ball.setPosition(150,150);
    

    }
    void Backpack::Pokeball_shoot(float& deltaTime, sf::RenderWindow& window, sf::Clock &clock2, sf::Time & elapsed2){
        
        
        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&(dict_pokeball["Normalball"]>0)&&new_Normalball.in_air ==false){
            
                    //Get the mouse position:
                    sf::Vector2i mousepixel = sf::Mouse::getPosition(window);
                    sf::Vector2f mouse_pos = window.mapPixelToCoords(mousepixel);
                    //std::cout<<mouse_pos.x<<'\n';
                    //std::cout<<mouse_pos.y<<'\n';
            
            //corresponds to the pokeball icon on the screen
            if((mouse_pos.x>20)&&(mouse_pos.x<57)&&(mouse_pos.y>150)&&(mouse_pos.y<190)){
                
                    dict_pokeball["Normalball"]-=1;
                
                    //std::cout<<dict_pokeball["Normalball"]<<'\n';
                    sf::Vector2u size = window.getSize();
                    float w = size.x;
                    float width = (float) w;
                    float h = size.y;
                    float height = (float) h + 2.0f;
                    float width4 = width/5;


                    new_Normalball.setPosition(width4, height);// Need to figure out where the starting x and y position are
                    new_Normalball.velocityY = -sqrt(5.0f * 981.0f * new_Normalball.ballHeight); //We need to reset the ball's position and starting speed when you shoot, that's why its in this class
                    new_Normalball.velocityX = 500;
                    new_Normalball.in_air = true;
            }
        }
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&(dict_pokeball["Superball"]>0)&&new_Superball.in_air ==false){
                       
                               //Get the mouse position:
                               sf::Vector2i mousepixel = sf::Mouse::getPosition(window);
                               sf::Vector2f mouse_pos = window.mapPixelToCoords(mousepixel);
                               //std::cout<<mouse_pos.x<<'\n';
                               //std::cout<<mouse_pos.y<<'\n';
                       
                       //corresponds to the pokeball icon on the screen
                       if((mouse_pos.x>70)&&(mouse_pos.x<107)&&(mouse_pos.y>150)&&(mouse_pos.y<190)){
                           
                               
                               dict_pokeball["Superball"]-=1;
                           
                               //std::cout<<dict_pokeball["Superball"]<<'\n';
                               sf::Vector2u size = window.getSize();
                               float w = size.x;
                               float width = (float) w;
                               float h = size.y;
                               float height = (float) h + 2.0f;
                               float width4 = width/5;


                               new_Superball.setPosition(width4, height);// Need to figure out where the starting x and y position are
                               new_Superball.velocityY = -sqrt(5.0f * 981.0f * new_Superball.ballHeight);//We need to reset the ball's position and starting speed when you shoot, that's why its in this class
                               new_Superball.velocityX = 500;
                               new_Superball.in_air = true;
                       }
                
            
        }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&(dict_pokeball["Masterball"]>0)&&new_Masterball.in_air ==false){
                           
                                   //Get the mouse position:
                                   sf::Vector2i mousepixel = sf::Mouse::getPosition(window);
                                   sf::Vector2f mouse_pos = window.mapPixelToCoords(mousepixel);
                                   //std::cout<<mouse_pos.x<<'\n';
                                   //std::cout<<mouse_pos.y<<'\n';
                           
                           //corresponds to the pokeball icon on the screen
                           if((mouse_pos.x>120)&&(mouse_pos.x<157)&&(mouse_pos.y>150)&&(mouse_pos.y<190)){
                               
                                   
                                   dict_pokeball["Masterball"]-=1;
                               
                                   //std::cout<<dict_pokeball["Masterball"]<<'\n';
                                   sf::Vector2u size = window.getSize();
                                   float w = size.x;
                                   float width = (float) w;
                                   float h = size.y;
                                   float height = (float) h + 2.0f;
                                   float width4 = width/5;


                                   new_Masterball.setPosition(width4, height);// Need to figure out where the starting x and y position are
                                   new_Masterball.velocityY = -sqrt(5.0f * 981.0f * new_Masterball.ballHeight); //We need to reset the ball's position and starting speed when you shoot, that's why its in this class
                                   new_Masterball.velocityX = 500;
                                   new_Masterball.in_air = true;
                           }
                    
                
            }
        
        //Continuation of the one shot as time goes by
        if (new_Normalball.in_air) {
                bool still_on_screen = new_Normalball.update(deltaTime, window,new_Normalball.proba, clock2, elapsed2);
                    //if the ball reached the end of the window, then the ball is not in air
                if (!still_on_screen) {
                            new_Normalball.in_air = false;

                }
        }
        //Continuation of the one shot as time goes by
        if (new_Superball.in_air) {
                bool still_on_screen = new_Superball.update(deltaTime, window,new_Superball.proba, clock2, elapsed2);
            
                    //if the ball reached the end of the window, then the ball is not in air
                if (!still_on_screen) {
                            new_Superball.in_air = false;
                }
        }
        //Continuation of the one shot as time goes by
        if (new_Masterball.in_air) {
                bool still_on_screen = new_Masterball.update(deltaTime, window,new_Masterball.proba, clock2, elapsed2);
                    //if the ball reached the end of the window, then the ball is not in air
                if (!still_on_screen) {
                            new_Masterball.in_air = false;

                }
        }
    }
    


//void Backpack::Pokeball_throw(Pokeball Pokeball,float& deltaTime, sf::RenderWindow& window){
//
//
//
//}
    
    
    void Backpack::draw (sf::RenderTarget &target) const {
        
        if(new_Normalball.in_air){
            target.draw(new_Normalball.ball);
        }
        if(new_Superball.in_air){
                   target.draw(new_Superball.ball);
               }
        if(new_Masterball.in_air){
                   target.draw(new_Masterball.ball);
               }
        
        target.draw(clickbox);
        target.draw(normalball);
        target.draw(superball);
        target.draw(masterball);
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

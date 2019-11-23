#include "Backpack.h"
#include<map>
#include<string>

Backpack::Backpack(){
    dict_pokeball["Normalball"] = 3;
}

void Backpack::Pokeball_shoot(float& deltaTime, sf::RenderWindow& window){
        
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
//            float i = 100;
//            new_Pokeball.setPosition(i, i);
//            std::cout << 'i' << std::endl;
//            window.draw(new_Pokeball.ball);
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

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <deque>
#include <vector>
#include "trainer_opponent.hpp"
using namespace std;

void Trainer_opponent::speak(sf::RenderWindow &window, sf::View &view, Trainer &trainer){
    if(beaten==false){
        if (fixed == true){
        this->draw(window);
    }

    else{
        if(trainer.facingDirection == "Down"){
            (spriteNpc).setTextureRect(sf::IntRect(sheetPosX,sheetPosY+sheetRectY,sheetRectX,sheetRectY));
            this->draw(window);
            }

        if(trainer.facingDirection == "Up"){
            (spriteNpc).setTextureRect(sf::IntRect(sheetPosX,sheetPosY,sheetRectX,sheetRectY));
            this->draw(window);
        }

        if(trainer.facingDirection == "Right"){
            (spriteNpc).setTextureRect(sf::IntRect(sheetPosX,sheetPosY+2*sheetRectY,sheetRectX,sheetRectY));
            this->draw(window);
        }

        if(trainer.facingDirection == "Left"){
            (spriteNpc).setTextureRect(sf::IntRect(sheetPosX + sheetRectX,sheetPosY+2*sheetRectY,-sheetRectX,sheetRectY));
            this->draw(window);
        }
    }


    if (speakCounter >= discussion.size()){
        if (trainer.state != "Shopping"){
            if (trainer.state != "Dead") trainer.state = "Stop";
            speakCounter = -1;

        }
        else speakCounter = 0;
    }

     else{
           if (discussion[speakCounter] == "Fighting"){
               trainer.fight_mode = 't';
               trainer.state = "Fighting";
               trainer.opponent_bag = &bag;
           }


           else{
               text.setString(discussion[speakCounter]);
               text.setCharacterSize(12);
               text.setFillColor(sf::Color::Black);
               text.setStyle(sf::Text::Bold);

               sf::FloatRect viewBounds = getViewBounds(view);
               bubble.setPointCount(8);
               bubble.setPoint(0, sf::Vector2f(float(viewBounds.left + 30), float(viewBounds.top + viewBounds.height - 60)));
               bubble.setPoint(1, sf::Vector2f(float(viewBounds.left + viewBounds.width - 30), float(viewBounds.top + viewBounds.height - 60)));
               bubble.setPoint(2, sf::Vector2f(float(viewBounds.left + viewBounds.width - 10), float(viewBounds.top + viewBounds.height - 45)));
               bubble.setPoint(3, sf::Vector2f(float(viewBounds.left + viewBounds.width - 10), float(viewBounds.top + viewBounds.height - 25)));
               bubble.setPoint(4, sf::Vector2f(float(viewBounds.left + viewBounds.width - 30), float(viewBounds.top + viewBounds.height - 10)));
               bubble.setPoint(5, sf::Vector2f(float(viewBounds.left + 30), float(viewBounds.top + viewBounds.height - 10)));
               bubble.setPoint(6, sf::Vector2f(float(viewBounds.left + 10), float(viewBounds.top + viewBounds.height - 25)));
               bubble.setPoint(7, sf::Vector2f(float(viewBounds.left + 10), float(viewBounds.top + viewBounds.height - 45)));
               bubble.setOutlineColor(sf::Color::Black);
               bubble.setOutlineThickness(2.f);
               text.setPosition(int(viewBounds.left) + 25, int(viewBounds.top + viewBounds.height - 40) );
               window.draw(bubble);
               window.draw(text);
        }
    }

    }
    else{
        this->draw(window);
    }
    
}

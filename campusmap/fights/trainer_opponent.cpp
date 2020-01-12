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
    cout<<"Speakok"<<endl;
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
               //std::cout<<"here"<<std::endl;
               //std::cout<<"ChEKCING1"<<(*(bag.backpack_pokemons[0])).name<<std::endl;
               trainer.fight_mode = 't';
               trainer.state = "Fighting";
               //std::cout<<"1 yes"<<std::endl;
               trainer.opponent_bag = &bag;
               //std::cout<<"2 yes"<<std::endl;
               //std::cout<<"checking1"<<(*(trainer.opponent_bag)).masternow<<std::endl;
               //std::cout<<"ChEKCING2"<<(*((*(trainer.opponent_bag)).backpack_pokemons[0])).name<<std::endl;
           }


           else{
               text.setString(discussion[speakCounter]);
               text.setCharacterSize(12);
               text.setFillColor(sf::Color::Black);
               text.setStyle(sf::Text::Bold);
               /* sf::Vector2f viewSize = view.getSize();
               bubble.setSize(sf::Vector2f(viewSize.x, viewSize.y/4)); */

               sf::FloatRect viewBounds = getViewBounds(view);
               bubble.setPointCount(8);
               bubble.setPoint(0, sf::Vector2f(float(viewBounds.left + 30), float(viewBounds.top + viewBounds.height - 60)));
               bubble.setPoint(1, sf::Vector2f(float(viewBounds.left + viewBounds.height - 30), float(viewBounds.top + viewBounds.height - 60)));
               bubble.setPoint(2, sf::Vector2f(float(viewBounds.left + viewBounds.height - 10), float(viewBounds.top + viewBounds.height - 45)));
               bubble.setPoint(3, sf::Vector2f(float(viewBounds.left + viewBounds.height - 10), float(viewBounds.top + viewBounds.height - 25)));
               bubble.setPoint(4, sf::Vector2f(float(viewBounds.left + viewBounds.height - 30), float(viewBounds.top + viewBounds.height - 10)));
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

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <deque>
#include <vector>
#include "npc.hpp"
using namespace std;

sf::FloatRect Npc::getViewBounds(const sf::View &view)
{
        sf::FloatRect rt;
        rt.left = view.getCenter().x - view.getSize().x/2.f;
        rt.top  = view.getCenter().y - view.getSize().y/2.f;
        rt.width  = view.getSize().x;
        rt.height = view.getSize().y;
        return rt;
}


Npc::Npc(int posX, int posY, vector<string> discu)
{
    if (!textureNpc.loadFromFile("Sprites/tileset1.png")) {
        cout << "Error loading sprite";
    }
    (spriteNpc).setTexture(textureNpc);
    spriteNpc.setTextureRect(sf::IntRect(392,52,16,16));
    spriteNpc.setScale(sf::Vector2f(1.1f, 1.1f));
    spriteNpc.setPosition(posX, posY);
    fixed = true;
    discussion = discu;
    speakCounter = -1;
    if (!font.loadFromFile("Fonts/sansation.ttf")) {
        cout << "Error in loading font" <<endl;
    }
    text.setFont(font);
    sheetRectX = 0;
    sheetRectY = 0;
}


Npc::Npc(string name, string pathName, int sheetPosX, int sheetPosY, int sheetRectX,int sheetRectY, float scale, int posX, int posY, vector<string> discu, bool fixed){
    
    this->name = name;
    
    if (!textureNpc.loadFromFile(/* resourcePath() + */ pathName)) {
        cout << "Error loading sprite";
    }
    (spriteNpc).setTexture(textureNpc);
    spriteNpc.setTextureRect(sf::IntRect(sheetPosX,sheetPosY,sheetRectX,sheetRectY));
    spriteNpc.setScale(sf::Vector2f(scale, scale));
    spriteNpc.setPosition(posX, posY);
    discussion = discu;
    speakCounter = -1;
    this->sheetPosX = sheetPosX;
    this->sheetPosY = sheetPosY;
    this->sheetRectX = sheetRectX;
    this->sheetRectY = sheetRectY;
    if (!font.loadFromFile(/* resourcePath() + */ "Fonts/sansation.ttf")) {
        cout << "Error in loading font" <<endl;
    }
    text.setFont(font);
    this->fixed = fixed;
}


void Npc::draw(sf::RenderWindow &window) const {
    window.draw(spriteNpc);
}

void Npc::speak(sf::RenderWindow &window, sf::View &view, Trainer &trainer){
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
      
    
    if (speakCounter == discussion.size()){
        if (trainer.state != "Shopping"){
            trainer.state = "Stop";
            speakCounter = -1;
            
        }
        else speakCounter = 0;
    }
    
     else{
           if (discussion[speakCounter] == "Shopping"){
               trainer.state = "Shopping";
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

void Npc::speakScenario(sf::RenderWindow &window, sf::View &view, Trainer &trainer, map<string,vector<string>> &scenario){
    
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
      
    if (scenario[name][0] == "Shopping"){
        trainer.state = "Shopping";
        scenario.erase("seller");
    }
    
    else{
        text.setString(scenario[name][0]);
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

sf::Vector2f Npc::getPos(){
    sf::Vector2f position = (spriteNpc).getPosition();
    return position;
}

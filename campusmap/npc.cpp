#include "npc.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <deque>
#include <vector>
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


Npc::Npc(string pathName, int sheetPosX, int sheetPosY, int sheetRectX,int sheetRectY, float scale, int posX, int posY, vector<string> discu){
    if (!textureNpc.loadFromFile(/* resourcePath() + */ pathName)) {
        cout << "Error loading sprite";
    }
    (spriteNpc).setTexture(textureNpc);
    spriteNpc.setTextureRect(sf::IntRect(sheetPosX,sheetPosY,sheetRectX,sheetRectY));
    spriteNpc.setScale(sf::Vector2f(scale, scale));
    spriteNpc.setPosition(posX, posY);
    discussion = discu;
    speakCounter = -1;
    this->sheetRectX = sheetRectX;
    this->sheetRectY = sheetRectY;
    if (!font.loadFromFile(/* resourcePath() + */ "Fonts/sansation.ttf")) {
        cout << "Error in loading font" <<endl;
    }
    text.setFont(font);
}


void Npc::draw(sf::RenderWindow &window) const {
    window.draw(spriteNpc);
}

void Npc::speak(sf::RenderWindow &window, sf::View &view, Trainer &trainer)  {
    
    /* cout << "Testoo" <<endl; */
    if(trainer.facingDirection == "Down"){
        (spriteNpc).setTextureRect(sf::IntRect(0,3*sheetRectY,sheetRectX,sheetRectY));
        this->draw(window);
    }
    
    if(trainer.facingDirection == "Up"){
        (spriteNpc).setTextureRect(sf::IntRect(0,0,sheetRectX,sheetRectY));
        this->draw(window);
    }
    
    if(trainer.facingDirection == "Right"){
        (spriteNpc).setTextureRect(sf::IntRect(0,sheetRectY,sheetRectX,sheetRectY));
        this->draw(window);
    }
    
    if(trainer.facingDirection == "Left"){
        (spriteNpc).setTextureRect(sf::IntRect(0,2*sheetRectY,sheetRectX,sheetRectY));
        this->draw(window);
    }
      

    if (speakCounter == discussion.size()){
        trainer.state = "Stop";
        speakCounter = -1;
    }
    
    else{
        
        text.setString(discussion[speakCounter]);
        text.setCharacterSize(15);
        text.setFillColor(sf::Color::Black);
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
        text.setPosition(int(viewBounds.left) + 35, int(viewBounds.top + viewBounds.height - 40) );
        /* bubble.setPosition(int(viewBounds.left), int(viewBounds.top + viewBounds.height - 50)); */

        
        window.draw(bubble);
        window.draw(text);
    }
}

sf::Vector2f Npc::getPos(){
    sf::Vector2f position = (spriteNpc).getPosition();
    return position;
}

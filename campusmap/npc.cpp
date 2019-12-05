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


Npc::Npc(string pathName, int sheetRectX,int sheetRectY, float scale , int posX, int posY, vector<string> discu) {
    if (!textureNpc.loadFromFile(/* resourcePath() + */ pathName)) {
        cout << "Error loading sprite";
    }
    (spriteNpc).setTexture(textureNpc);
    spriteNpc.setTextureRect(sf::IntRect(0,0,sheetRectX,sheetRectY));
    spriteNpc.setScale(sf::Vector2f(scale, scale));
    spriteNpc.setPosition(posX, posY);
    discussion = discu;
    speakCounter = 0;
}


void Npc::draw(sf::RenderWindow &window) const {
    window.draw(spriteNpc);
}

void Npc::speak(sf::RenderWindow &window, sf::View &view)  {
    
    if (!font.loadFromFile(/* resourcePath() + */ "Fonts/sansation.ttf")) {
        cout << "Error in loading font";
    }
    if(speakCounter == discussion.size()){
        speakCounter = 0;
    }
    text.setFont(font); 
    text.setString(discussion[speakCounter]);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    sf::Vector2f viewSize = view.getSize();
    bubble.setSize(sf::Vector2f(viewSize.x, viewSize.y/4));

    sf::FloatRect viewBounds = getViewBounds(view);

    text.setPosition(int(viewBounds.left), int(viewBounds.top + viewBounds.height - 50) );
    bubble.setPosition(int(viewBounds.left), int(viewBounds.top + viewBounds.height - 50));

    text.setStyle(sf::Text::Bold);
    
    window.draw(bubble);
    window.draw(text);
    speakCounter ++ ; 
}

sf::Vector2f Npc::getPos(){
    sf::Vector2f position = (spriteNpc).getPosition();
    return position;
}
#pragma once


#include "Backpack.h"
#include "../npc.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class Trainer_opponent: public Npc{
    public:
        Trainer_opponent(string name, string pathName, int sheetPosX, int sheetPosY, int sheetRectX,int sheetRectY, 
                        float scale, int posX, int posY, vector<string> discu, bool fixed, int i):
                        Npc (name, pathName, sheetPosX, sheetPosY, sheetRectX, sheetRectY,
                        scale, posX, posY, discu, fixed  /*everything except backpack*/){
                            bag.setBackpack(i);
                        };

        virtual void speak(sf::RenderWindow &window, sf::View &view, Trainer &trainer);

        Backpack bag;
};
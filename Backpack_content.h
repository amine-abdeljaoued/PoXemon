#pragma once
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

//We carry this backpack throughout the game
//->we need to talk with the other teams for that

class Backpack
{
    public:
        Backpack();
        std::map<std::string, int> inventory;
        std::map<std::string, int> cost;
        int num_item();
        int capacity;
        int wallet;
        sf::Text money;
    private:
        int number;
};

const std::string item_type[] = {
    "Normalball","Superball", "Masterball", "Incubator", "Starpowder", "SmallHealthPotion", "BigHealthPotion"
};

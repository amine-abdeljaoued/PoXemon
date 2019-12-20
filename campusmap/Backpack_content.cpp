#include "Backpack_content.h"
#include <map>
#include <string>
#include <cmath>
#include <iostream>
#include <iterator>
#include <algorithm>


Backpack::Backpack(){
    
    //Set number of element of each item at beginning of game
    inventory["Normalball"] = 12;
    inventory["Superball"] = 7;
    inventory["Masterball"] = 3;
    inventory["Incubator"] = 2;
    inventory["Starpowder"] = 13;
    inventory["SmallHealthPotion"] = 6;
    inventory["BigHealthPotion"] = 2;
    
    //Set maximal capacity of backpack
    capacity = 100;
    
    //Set cost of each item in shops
    cost["Normalball"] = 10;
    cost["Superball"] = 20;
    cost["Masterball"] = 50;
    cost["Incubator"] = 100;
    cost["Starpowder"] = 30;
    cost["SmallHealthPotion"] = 40;
    cost["BigHealthPotion"] = 70;
    
    //Set amount of money you have at beginning of game
    wallet = 300;
    }

//Method that returns total number of items in your backpack
int Backpack::num_item() {
    
    //reset to 0
    number = 0;
 
    // Create a map iterator and point to beginning of map
    std::map<std::string, int>::iterator it = inventory.begin();
 
    // Iterate over the map using Iterator till end.
    while (it != inventory.end())
    {
        // Accessing number from the item pointed by it.
        int count = it->second;
 
        number += count;
 
        // Increment the Iterator to point to the next item
        it++;
    }
    return number;
}

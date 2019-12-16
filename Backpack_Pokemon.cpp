#pragma once
#include "Pokemon_button.h"

class Backpack_Pokemon { 
public:
	Backpack_Pokemon(std::string n, int lvl, int i, int h) {
		name = n;
		level = lvl;
		index = i;
		health = h;
		button = Pokemon_Button(name, level, health, index); //not very good code (same info in two different classes)
	}

	std::string name;
	int index;//to find it easily
	int health;
	int level;
	Pokemon_Button button;
};

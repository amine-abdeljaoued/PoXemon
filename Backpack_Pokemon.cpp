#pragma once
#include "Pokemon_button.h"

class Backpack_Pokemon { 
public:
	Backpack_Pokemon(std::string n, int lvl, int i, int h, int ptype) {
		name = n;
		level = lvl;
		index = i;
		health = h;
		button = Pokemon_Button(name, level, health, index); //not very good code (same info in two different classes)
		type = ptype;
	}

	std::string name;
	int index;//to find it easily
	int health;
	int level;
	int type;
	Pokemon_Button button;
};

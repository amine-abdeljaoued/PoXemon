#pragma once
#ifndef intro_hpp
#define intro_hpp
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>

int intro(std::string, bool, int);
bool choice(std::string, bool, int);
int choose(std::string, bool);
int menu(std::string);
int loadgame(std::string);
int startgame();

#endif /* intro_hpp */

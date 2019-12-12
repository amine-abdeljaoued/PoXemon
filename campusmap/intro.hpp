//
//  intro.hpp
//  Pokemen
//
//  Created by Julien Luzzatto on 05/12/2019.
//  Copyright © 2019 Julien Luzzatto. All rights reserved.
//
#pragma once

#ifndef intro_hpp
#define intro_hpp
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>

int intro(std::string, bool, int);
bool choice(std::string, bool, int);
int choose(std::string, bool);

#endif /* intro_hpp */

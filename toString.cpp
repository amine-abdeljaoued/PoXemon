#include "toString.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>

template <typename T>
std::string toString(T arg){
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

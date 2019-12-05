
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "menu.hpp"
#include "intro.hpp"
#include <iostream>


int main(int, char const**)
{
    // Create successively the main window
    menu("main_menu.jpg");
    intro("professor5.png",1,0);
    intro("professor2.png",1,1);
    intro("professor3.png",0,2);
    intro("professor1.png",0,3);
    intro("professor4.png",0,4);
    intro("professor5.png",1,5);
    intro("professor7.png",1,6);
    intro("professor1.png",0,7);
    intro("professor2.png",0,8);
    intro("professor1.png",1,9);
    intro("professor2.png",1,10);
    intro("professor3.png",0,11);
    intro("professor4.png",0,12);
    intro("professor6.png",1,13);
    intro("professor7.png",1,14);
    intro("professor1.png",0,15);
    intro("professor2.png",0,16);
    intro("professor2.png",1,17);

    return EXIT_SUCCESS;
}

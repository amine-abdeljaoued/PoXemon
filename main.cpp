
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
    menu("main_menu.jpg");
    intro("professor1.png",1,0);
    intro("professor4.png",1,1);
    intro("professor3.png",0,2);
    intro("professor5.png",0,3);
    intro("professor2.png",0,4);
    intro("professor6.png",1,5);
    intro("professor7.png",1,6);
    intro("professor1.png",0,7);
    intro("professor4.png",0,8);
    intro("professor6.png",1,9);
    intro("professor5.png",1,10);
    intro("professor3.png",0,11);
    intro("professor2.png",0,12);
    choice("professor0.png",1,13);
    if(choice("professor0.png",1,14)==1){
        intro("professor7.png",0,15);
    }
    else{
    intro("professor4.png",0,16);
    intro("professor1.png",1,17);
        int a = choose("professor0.png",1);
        if(a==1){
            intro("professor5.png",0,18);
        }
        else if(a==2){
            intro("professor5.png",0,19);
        }
        else if(a==3){
            intro("professor5.png",0,20);
        }
    }
    return EXIT_SUCCESS;
}

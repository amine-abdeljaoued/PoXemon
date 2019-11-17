#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

/*
 Remember to change the file path in the names of the sprite documents 
 
 Ok so the layout of this is very messy because I haven't set up the virtual maching and macs are a nightmare. let me explain what's happening:
 
 - First we have the pokeball class
 - Then the pokemon class
 - Then the main
 
 In the pokemon class you have methods to mvoe and shoot. At this point I've given the Pokemon one specific Pokeball, which we need to change at a later point - this also means the shoot function will also have change at a later point. For now I just wanted to see if I could get it to shoot (and it's hard to include all of that lol, so that's what I did)
 ** The shoot function is very messy
 
 The Pokeball class controls the basics of the pokeballs, I've controlled the movement inside the Pokemon class - but I think this should change, especially if we want to use sprite sheets with a rotating ball, etc
 
 Some basics things we should add soon:
 - Borders so that our lowerbound (groundX and groundY) are not based on fixed values but rather based on collisions: see here for a good tutorial https://www.youtube.com/watch?v=6WopQvdNRSA&t=30s
 - Also should figure how to move, right now all values are trial and error to get the pokemon and ball in a nice position with nice sizes, but there should be a better way
 - Sprite sheets
 - Then health and try figure out the other character
 
 */

float groundY = 300.0f; //Cannot go below this height
float groundX = 1000.f;

class Pokeball{
public:
    float velocityX;
    float x;
    float y;
    float speed = 1; //Set the speed of each of the pokeballs
    float power;// To know how much the health is reduced when hit
    sf::Sprite ball;
    
    Pokeball(){   // Thing to add: should also initialise ball                                            image, with views for rotation
        sf::Texture pic;
        pic.loadFromFile("/Users/anyafries/Desktop/SFML/SFML Template/SFML Template/pokeball.png");
        ball.setTexture(pic);
        ball.setScale(sf::Vector2f(0.4f, 0.4f));
    }
    void dissapear(){
        ball.setPosition(500.f, 2000.f);
        // I just set this randomly, we must figure out if we wan't to delete the balls, keep them in pokemon class/etc...
    }
    void setPosition(float &xpos, float &ypos){
        x = xpos;
        y = ypos;
        ball.setPosition(xpos, ypos);
    }
};

class Pokemon{
public:
    sf::Sprite sprite;
    float x;                //x and y store current position
    float y;
    float speed;            //Determines how far pokemon moves each time you press l/r
    float velocityX;
    float velocityY = 0;    //will be needed to jump
    float accY;
    Pokeball ball;
    float jumpHeight;       //how high this pokemon can jump
    bool canJump;           //If you're on the ground, you can jump
    bool shooting;          //If you're shooting, we want to draw the pokeball
    
    Pokemon(float xstart, float ystart, float h, float v)
    {
        jumpHeight = h;
        speed = v;
        canJump = true;
        shooting = false;
        x = xstart;
        y = ystart;
        sprite.setPosition(sf::Vector2f(x, y));
        sf::Texture pic;
        pic.loadFromFile("/Users/anyafries/Desktop/SFML/SFML Template/SFML Template/eevee.png");
        sprite.setTexture(pic);
        sprite.setScale(sf::Vector2f(0.4f, 0.4f));
    }
    
    void update(float &deltaTime){   // Movement is dependant on time not on frame rate
                                    // This means that we can have smooth movement over multiple frames, instead of static movement per each frame
        velocityX = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            velocityX -= speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            velocityX += speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && canJump){
            canJump = false;       //While jumping you can't jump
            velocityY = -sqrt(2.0f * 981.0f * jumpHeight);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            ball.setPosition(x, y);
            shooting = true;
        }
        
        velocityY += 981.0f*deltaTime;
        if (shooting){
            ball.velocityX += ball.speed;
        }
        
        move(deltaTime);
    }
    

    
    void move(float &deltaTime){
        x += velocityX * deltaTime;
        y += velocityY * deltaTime;
        if(y >= groundY){
            y = groundY;
            velocityY = 0.0f;
            canJump = true;
        }
        
        if (shooting){
            ball.x += ball.velocityX * deltaTime;
            if (ball.x >= groundX){     // Ball off the screen, we want to remove it from                               visible, to avoid any complications
                ball.dissapear();
                shooting = false;
            }
            else{
                ball.setPosition(ball.x, ball.y); // Otherwise we update it's position
            }
        }
        sprite.setPosition(x, y);
    }
};

int main ()
{
    sf::RenderWindow window(sf::VideoMode(1400, 700), "My window");
    //video mode defines the size of the window
    //constructor accepts a third optional argument: a style (decorations and features)
    //see https://www.sfml-dev.org/tutorials/2.5/window-window.php
    
    Pokemon eevee(10.0f, groundY, 200.f, 500.f);
    float deltaTime = 0.0f;
    sf::Clock clock;
    // run the program as long as the window is open
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            {
                std::cout<<"Goodbye"<<std::endl;
                window.close();
            }
        }

        // clear the window with black color - need to clear before drawing anything (overlap)
        eevee.update(deltaTime);
        window.clear(sf::Color::Blue);
        window.draw(eevee.sprite);
        
        if (eevee.shooting){
            window.draw(eevee.ball.ball);
        }

        // end the current frame - mandatory: takes what was drawn since the last call to display and displays it on the window
        window.display();
    }
}

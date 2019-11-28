
#include "Pokeball.h"




    Pokeball::Pokeball() {   // Thing to add: should also initialise ball                                            image, with views for rotation
        pic.loadFromFile("Images/pokeball.png");
        ball.setTexture(pic);
        ball.setScale(sf::Vector2f(0.4f, 0.4f));
        in_air = false;
        bounce = false;
    }
    void Pokeball::dissapear() {
        ball.setPosition(200.f, 2000.f);
        bounce=false;
        // I just set this randomly, we must figure out if we wan't to delete the balls, keep them in pokemon class/etc...
    }
    void Pokeball::setPosition(float& xpos, float& ypos) {
        x = xpos;
        y = ypos;
        ball.setPosition(xpos, ypos);
    }

    

    bool Pokeball::update(float deltaTime,sf::RenderWindow& window) {
        //update the velocityY of the pokeball using low gravity and airfriction
        velocityY += gravity * deltaTime - airfriction * velocityY * deltaTime;
        x += velocityX * deltaTime - airfriction * velocityX * deltaTime;
        y += velocityY * deltaTime;
        
        setPosition(x, y);
        
        
        sf::Vector2u size = window.getSize();
        float w = size.x;
        float width = (float) w;
        
        float groundX = width;
        float bounceX = 0.6 * width;
        
        if ((x >= bounceX)&&(bounce==false)) {     // does the bounce only one time
            velocityY = -velocityY;
            bounce=true;
        }
        if (x >= groundX) {     // Ball off the screen, we want to remove it from                               visible, to avoid any complications
            dissapear();
            return false;
        }
        //window.draw(ball);
        return true;
    }


Normalball::Normalball() {  //derived class
        proba = 0.20;
        pic1.loadFromFile("Images/pokeball.png");
        ball.setTexture(pic1);
        ball.setScale(sf::Vector2f(0.4f, 0.4f));
}

Superball::Superball() {  //derived class
        proba = 0.40;
        pic2.loadFromFile("Images/pokeball.png");
        ball.setTexture(pic2);
        ball.setScale(sf::Vector2f(0.4f, 0.4f));
}

Masterball::Masterball() {  //derived class
        proba = 0.60;
        pic3.loadFromFile("Images/pokeball.png");
        ball.setTexture(pic3);
        ball.setScale(sf::Vector2f(0.4f, 0.4f));
}

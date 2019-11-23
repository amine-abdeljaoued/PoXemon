#include "Health.h"

Healthbar::Healthbar(){
    setHealth(100);
    //Little heart next to bar - numbers used just work, don't know how to make them nice
    if (!heart_pic.loadFromFile("Images/heart.png")){ std::cout << "could not load" << std::endl;}
    heart_pic.loadFromFile("Images/heart.png");
    heart.setTexture(heart_pic);
    heart.setScale(sf::Vector2f(0.75, 0.75));
    //Size of outline and bar must be initialised to the same size, later bar will change
    //Outline with white base
    outline.setFillColor(sf::Color::White);
    outline.setOutlineThickness(4);
    outline.setOutlineColor(sf::Color::Black);
    outline.setSize(sf::Vector2f(100,20));
    // Moving bar that shows the health
    // Later: animate it
    bar.setFillColor(sf::Color(0,255,0));   // Initially green
    bar.setSize(sf::Vector2f(100,20));
    setPosition(50,50);                     // Both bars and the heart must move together
    update();
}

int Healthbar::getHealth(){
    return health;
}

void Healthbar::setPosition(float x, float y){
    outline.setPosition(x,y);
    bar.setPosition(x,y);
    heart.setPosition(x-27,y-10);           // Heart slightly left and up to the bar (random choice, works well)
}

void Healthbar::setHealth(int a){
    health = a;
    update();
}

void Healthbar::update(){
    bar.setSize(sf::Vector2f(health,20));
    //Bar changes from green to red as health decreases
    if (health > 50){
        bar.setFillColor(sf::Color((100-health)*2.55*2, 255,0));
    }
    else{bar.setFillColor(sf::Color(255, health*2.55*2,0));}
}

void Healthbar::draw(sf::RenderTarget& target) const {
    // Object drawn last is on top
    target.draw(outline);
    target.draw(bar);
    target.draw(heart);
} 
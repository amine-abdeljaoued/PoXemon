#include "Health.h"

Healthbar::Healthbar(){
    //Text
    if (!font.loadFromFile("fights/upheavtt.ttf")) { std::cout << "could not load bullet_bar font" << std::endl; }
	name_text.setFont(font);
    level_text.setFont(font);
	name_text.setCharacterSize(35);
    level_text.setCharacterSize(25);
    name_text.setFillColor(sf::Color::Black);
    level_text.setFillColor(sf::Color::Black);

    //Background bar with name, level, etc...
    if (!bar_pic.loadFromFile("fights/Images/bar.png")){ std::cout << "could not load" << std::endl;}
    bar_pic.loadFromFile("fights/Images/bar.png");
    bar.setTexture(bar_pic);
    bar.setScale(sf::Vector2f(0.2,0.2));

    //Little heart next to bar - numbers used just work, don't know how to make them nice
    if (!heart_pic.loadFromFile("fights/Images/heart.png")){ std::cout << "could not load" << std::endl;}
    heart_pic.loadFromFile("fights/Images/heart.png");
    heart.setTexture(heart_pic);
    heart.setScale(sf::Vector2f(0.55, 0.55));

    //Size of outline and bar must be initialised to the same size, later bar will change
    //Outline with white base
    healthwidth = 120;
    healthheight = 15;
    outline.setFillColor(sf::Color::White);
    outline.setOutlineThickness(4);
    outline.setOutlineColor(sf::Color::Black);
    outline.setSize(sf::Vector2f(120,15));

    // Moving bar that shows the health
    // Later: animate it
    healthbar.setFillColor(sf::Color(0,255,0));   // Initially green
    healthbar.setSize(sf::Vector2f(120,15));
    setPosition(50,50);                     // Both bars and the heart must move together
    update();

}

int Healthbar::getHealth(){
    return health;
}

void Healthbar::setPosition(float x, float y){
    // Background
    bar.setPosition(x,y);
    //Text
    name_text.setPosition(x+ bar.getGlobalBounds().width * 1/10, y + (1/5)*bar.getGlobalBounds().height);
    // Health bar + level
    float x1 = x + bar.getGlobalBounds().width/2;
    float y1 = y + bar.getGlobalBounds().height * 3/5;
    level_text.setPosition(x+ bar.getGlobalBounds().width * 1/10, y1 - 10);
    outline.setPosition(x1,y1);
    healthbar.setPosition(x1,y1);
    heart.setPosition(x1-23,y1-8);           // Heart slightly left and up to the bar (random choice, works well)
}

void Healthbar::setHealth(int a){
    health = a;
    update();
}

void Healthbar::decrease(int i) {
	health -= i;
}

void Healthbar::update(){
    //Text
    name_text.setString(name);
    level_text.setString("lvl: " + std::to_string(level));
    //Size
    if (health>0){
        healthbar.setSize(sf::Vector2f(health*healthwidth/100, healthheight));
    }
    else{
        healthbar.setSize(sf::Vector2f(0, healthheight));
        health = 0;
        }
    //Bar changes from green to red as health decreases
    if (health > 50){
        healthbar.setFillColor(sf::Color((100-health)*2.55*2, 255,0));
    }
    else{healthbar.setFillColor(sf::Color(255, health*2.55*2,0));
    }
}

void Healthbar::draw(sf::RenderWindow& target) const {
    // Object drawn last is on top
    target.draw(bar);
    target.draw(outline);
    target.draw(healthbar);
    target.draw(heart);
    target.draw(name_text);
    target.draw(level_text);
} 

void Healthbar::draw(sf::RenderTexture& texture) const {
    texture.draw(bar);
    texture.draw(outline);
    texture.draw(healthbar);
    texture.draw(name_text);
    texture.draw(level_text);
    texture.draw(heart);
}
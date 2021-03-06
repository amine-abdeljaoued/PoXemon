#include "Pokeball.h"
#include<random>



    Pokeball::Pokeball() {   // Thing to add: should also initialise ball                                            image, with views for rotation
        //pic.loadFromFile("Images/pokeball.png");
        //ball.setTexture(pic);
        ball.setScale(sf::Vector2f(0.4f, 0.4f));
        in_air = false;
        bounce = 0;
        waiting=false;
    }


    void Pokeball::dissapear() {
        ball.setPosition(200.f, 2000.f);
        waiting = false;
        bounce=0;
        // I just set this randomly, we must figure out if we wan't to delete the balls, keep them in pokemon class/etc...
    }
    void Pokeball::setPosition(float& xpos, float& ypos) {
        x = xpos;
        y = ypos;
        ball.setPosition(xpos, ypos);
    }

    void Pokeball::reset(){
        bounce = 0;
        ball.setPosition(200.f, 2000.f);
        waiting = false;
    }


    int Pokeball::update(float deltaTime,sf::RenderWindow& window,float proba, sf::Clock &clock2, sf::Time &elapsed2, float opphealth) {
        //update the velocityY of the pokeball using low gravity and airfriction
        velocityY += gravity * deltaTime - airfriction * velocityY * deltaTime;
        x += velocityX * deltaTime - airfriction * velocityX * deltaTime;
        y += velocityY * deltaTime;

        setPosition(x, y);
        //Accessing to the health of the opponent to determine a better proba of catching the pokeball

        //std::cout<<opphealth<<std::endl;

        sf::Vector2u size = window.getSize();
        float w = size.x;
        float width = (float) w;
        float z = size.y;
        float height = (float) z;
        float miheight = height/2;
        float groundX = width;
        float bounceX = 0.4 * width;


        if ((x >= bounceX)&&(bounce<8)&&(y>=miheight)) {     // does the bounce only one time
            float counter =0;
            velocityY = -velocityY + coefimpact* velocityY;
            y-=5;
            if (bounce == 0){
                velocityX -=200;
            }
            else{
                if (velocityX-60>=0){
                    velocityX -= 60;
                }
                else{
                    velocityX = 0;
                }
            }

            bounce+=1;
            //std::cout<<bounce<<std::endl;
        }
        if (bounce==7){
            velocityY = 0;
            velocityX = 0;
            bounce+=1;
        }

        if (bounce>7){
            waiting = true;
//            if (bounce == 50){
//                velocityX-=30;
//            }
//            else{
            velocityY = 0;
            velocityX = 0;
            //}
            //catched(proba, clock2, elapsed2);

            //if (catched(proba, clock2, elapsed2,opphealth)){
                //dissapear();
            //    return 1;
           // }

            //std::cout<<proba<<std::endl;
//            if (catched(proba)){
//                dissapear();
//            };
        }
        if ((x >= groundX)||((x>=width/2)&&(y>height))) {     // Ball off the screen, we want to remove it from                               visible, to avoid any complications
            //dissapear();
            //return 0;
        }
        //window.draw(ball);
        //return 0;

		return catched(proba, clock2, elapsed2, opphealth);
    }

int Pokeball::catched(float proba, sf::Clock& clock2, sf::Time& elapsed2,float opphealth){//0 if nothing, 1 if catched, 2 if not catched
    // //Prints the elapsed time
    //std::cout<<elapsed2.asSeconds()<<std::endl;

    //Not very beautiful way to restart the clock at the eight bounce since the
    //clock is running since the throw
    if (elapsed2.asSeconds() > 7.0f) {
        clock2.restart();
        return 0;
    }
    //wait 3 seconds to catch the pokemon
    if (elapsed2.asSeconds() > 6.0f) {
        clock2.restart();

        //compares a random number between 0 and 1 with the proba of the ball

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        //for (int n = 0; n < 3; ++n) {
        // double in [1, 2). Each call to dis(gen) generates a new random double
        //std::cout << dis(gen) << ' ';
        //}

        float probagenerated = dis(gen);
        //std::cout<< "proba generated: "<<probagenerated <<std::endl;
        //std::cout<<"proba modified: "<<proba +(proba+0.4)*((100-opphealth)/100)<<std::endl;

        //now it works in fct of the life of the opponent
        //the term (proba+0.4)*((100-opphealth)/100) increaments the chnace of catching the pokemons if it is low life
        if (probagenerated < proba + ((proba+0.4)*((100-opphealth)/100))){
            std::cout<<"Catched !"<<std::endl;
            return 1;
        }
        else{
            std::cout<<"Not Catched !"<<std::endl;
            return 2;
        }


    }

    }


Normalball::Normalball() {  //derived class
        proba = 0.20;
        pic1.loadFromFile("fights/Images/pokeball.png");
        ball.setTexture(pic1);
        ball.setScale(sf::Vector2f(0.25f, 0.25f));
}

Superball::Superball() {  //derived class
        proba = 0.30;
        pic2.loadFromFile("fights/Images/superball.png");
        ball.setTexture(pic2);
        ball.setScale(sf::Vector2f(0.25f, 0.25f));
}

Masterball::Masterball() {  //derived class
        proba = 0.60;
        pic3.loadFromFile("fights/Images/masterball.png");
        ball.setTexture(pic3);
        ball.setScale(sf::Vector2f(0.07f, 0.07f));
}

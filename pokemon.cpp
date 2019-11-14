#include <iostream>
#include <string>

#include "pokemon.h"
using namespace std;

Pokemon::Pokemon(){
  initial_hp = 100;
  hp = 100;
  first_attack_name = "first";
  first_attack = 50;
  second_attack_name = "second";
  second_attack = 50;
  third_attack_name = "third";
  third_attack = 50;
}

bool Pokemon::isAlive(){
    if (hp>0)
    {
      return true;
    }
    else
    {
      return false;
    }
};

void Pokemon::inDamage(int damage){ //our Pokemon sadly received an attack
    hp = hp - damage;
    if (hp < 0) //not a negative life
    {
       hp = 0; //our Pokemon sadly collapsed
    }
};

void Pokemon::firstAttack(Pokemon &enemy){
    enemy.inDamage(first_attack); //the enemy suffers the attack's damage
};

void Pokemon::secondAttack(Pokemon &enemy){
    enemy.inDamage(second_attack); //the enemy suffers the attack's damage
};

void Pokemon::thirdAttack(Pokemon &enemy){
    enemy.inDamage(third_attack); //the enemy suffers the attack's damage
};

void Pokemon::inPotion(int howmuchPotion){
    hp = hp + howmuchPotion;
    if (hp > initial_hp) //our Pokemon cannot have more hp than the inital hp
    {
       hp = initial_hp; //our Pokemon is essentially in a good shape
    }
};

int main()
{
    Pokemon david, maxence;
    //Création de 2 objets de type Personnage : david et goliath

    david.firstAttack(maxence); //goliath attaque david
    maxence.inPotion(20); //david récupère 20 de vie en buvant une potion
    std::cout << "/* Maxence's hp: " << maxence.hp << "*/" << '\n';

    return 0;
}

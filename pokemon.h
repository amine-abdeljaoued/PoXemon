#pragma once
#define new_Pokemon
#include <string>

class Pokemon
{
    private:

    int initial_hp;
    // int attack; we might use it
    // int defense; we might use it
    // int speed; we might use it
    // int special; we might use it
    std::string first_attack_name;
    int first_attack;
    std::string second_attack_name;
    int second_attack;
    std::string third_attack_name;
    int third_attack;


    public:

    int hp;
    Pokemon();
    bool isAlive();
    void inDamage(int damage);
    void firstAttack(Pokemon &enemy);
    void secondAttack(Pokemon &enemy);
    void thirdAttack(Pokemon &enemy);
    void inPotion(int howmuchPotion);

};

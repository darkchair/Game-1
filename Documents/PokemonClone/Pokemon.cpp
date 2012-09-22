#include "Pokemon.h"


Pokemon::Pokemon() {

/*    pokeMoveSet.push_back(new Move(20));
    pokeMoveSet.push_back(new Move(30));
    pokeMoveSet.push_back(new Move());
    pokeMoveSet.push_back(new Move());*/

    stamina = 100;
    maxStamina = 100;
    attack = 10;
    defense = 11;
    sattack = 20;
    sdefense = 21;
    speed = 30;
    criticalStage = 1;
    status = 0;

    for(int i=0; i<9; i++)
        elementChangeTracker.push_back(0);

}

Pokemon::Pokemon(int elem) {

/*    pokeMoveSet.push_back(new Move(20));
    pokeMoveSet.push_back(new Move(30));
    pokeMoveSet.push_back(new Move());
    pokeMoveSet.push_back(new Move());*/

    nickname = "-NoName-";
    element = elem;
    stamina = 100;
    maxStamina = 100;
    attack = 10;
    defense = 11;
    sattack = 20;
    sdefense = 21;
    speed = 30;
    criticalStage = 1;
    status = 0;

    for(int i=0; i<9; i++)
        elementChangeTracker.push_back(0);

}

Pokemon::Pokemon(int elem, std::string name) {

/*    pokeMoveSet.push_back(new Move(20));
    pokeMoveSet.push_back(new Move(30));
    pokeMoveSet.push_back(new Move());
    pokeMoveSet.push_back(new Move());*/

    nickname = name;
    element = elem;
    stamina = 100;
    maxStamina = 100;
    attack = 10;
    defense = 11;
    sattack = 20;
    sdefense = 21;
    speed = 30;
    criticalStage = 1;
    status = 0;

    for(int i=0; i<9; i++)
        elementChangeTracker.push_back(0);

}

//--------------------------------------------------------------------

std::string Pokemon::getNickname() {

    return nickname;

}

int Pokemon::getStamina() {

    return stamina;

}

int Pokemon::getMaxStamina() {

    return maxStamina;

}

int Pokemon::getAttack() {

    return attack;

}

int Pokemon::getDefense() {

    return defense;

}

int Pokemon::getSAttack() {

    return sattack;

}

int Pokemon::getSDefense() {

    return sdefense;

}

int Pokemon::getSpeed() {

    return speed;

}

int Pokemon::getElement() {

    return element;

}


Move* Pokemon::getMove(int chosenMove) {

    return pokeMoveSet.at(chosenMove);

}

int Pokemon::getStatus() {

    return status;

}


void Pokemon::setStamina(int stam) {

    stamina = stam;

}

void Pokemon::setStatus(int sts) {

    status = sts;

}

void Pokemon::addMove(Move* move) {

    pokeMoveSet.push_back(move);

}



bool Pokemon::isCriticalHit() {

    double success = 0;
    if(criticalStage == 1)
        success = 6;
    if(criticalStage == 2)
        success = 12;
    if(criticalStage == 3)
        success = 25;
    if(criticalStage == 4)
        success = 33;
    if(criticalStage == 5)
        success = 50;

    int randomNumber = rand() % 100 + 1;

    if(randomNumber < success)
        return true;

    return false;

}

bool Pokemon::isSniper() {

    return sniper;

}

bool Pokemon::isBurned() {

    return burned;

}

bool Pokemon::hasLightScreen() {

    return lightScreen;

}

bool Pokemon::hasReflect() {

    return reflect;

}




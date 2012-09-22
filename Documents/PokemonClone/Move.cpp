#include "Move.h"


std::vector<Move*> Move::moveDataSet;

std::vector<std::string> Move::moveNames;


Move::Move() {

    id = rand() % 36;
    special = Move::moveDataSet.at(id)->special;
    multiHit = Move::moveDataSet.at(id)->multiHit;
    power = Move::moveDataSet.at(id)->power;
    element = Move::moveDataSet.at(id)->element;
    priorityLevel = Move::moveDataSet.at(id)->priorityLevel;

    name = Move::moveNames.at(id);


    /*element = rand() % 9;

    if(element == 0)
        name = "Martial";
    else if(element == 1)
        name = "Mental";
    else if(element == 2)
        name = "Spirit";
    else if(element == 3)
        name = "Fire";
    else if(element == 4)
        name = "Water";
    else if(element == 5)
        name = "Wood";
    else if(element == 6)
        name = "Electric";
    else if(element == 7)
        name = "Ground";
    else if(element == 8)
        name = "Metal";
    else
        name = "None";*/

}

Move::Move(std::string nm) {

    name = nm;

    int randomNumber = rand() % 9;

    element = randomNumber;

}

Move::Move(int theId) {

    id = theId;
    special = Move::moveDataSet.at(theId)->special;
    multiHit = Move::moveDataSet.at(theId)->multiHit;
    power = Move::moveDataSet.at(theId)->power;
    element = Move::moveDataSet.at(theId)->element;
    priorityLevel = Move::moveDataSet.at(theId)->priorityLevel;

    name = Move::moveNames.at(id);

}

Move::Move(int tempID, bool tempSpecial, bool tempMulti, int tempPower, int tempElement, int tempPriority) {

    id = tempID;
    special = tempSpecial;
    multiHit = tempMulti;
    power = tempPower;
    element = tempElement;
    priorityLevel = tempPriority;

}

std::string Move::getName() {

    return name;

}

int Move::getID() {

    return id;

}

int Move::getElement() {

    return element;

}

int Move::getPriorityLevel() {

    return priorityLevel;

}



bool Move::isSpecialAttack() {

    return special;

}

bool Move::isHitsMultiple() {

    return multiHit;

}

double Move::getPower() {

    return power;

}

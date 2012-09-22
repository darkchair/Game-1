#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

class Move {

public:

    Move();

    Move(std::string nm);

    Move(int theId);

    Move(int tempID, bool tempSpecial, bool tempMulti, int tempPower, int tempElement, int tempPriority);

public:

    static std::vector<Move*> moveDataSet;

    static std::vector<std::string> moveNames;

private:

    std::string name;

    int  id;

    bool special;

    bool multiHit;

    int  power;

    int  element;

    int  priorityLevel;

public:

    std::string getName();

    int getID();

    double getPower();

    int getElement();

    int getPriorityLevel();


    bool isSpecialAttack();

    bool isHitsMultiple();



};

#endif // MOVE_H_INCLUDED

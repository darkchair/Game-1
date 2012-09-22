#ifndef ENEMYINTERCEPTOR_H_INCLUDED
#define ENEMYINTERCEPTOR_H_INCLUDED

#include <vector>
#include <stdio.h>
#include <string>
#include <stdlib.h>

struct Coordinate {
    int x;
    int y;
};

class EnemyInterceptor {

    public:

        EnemyInterceptor();

    public:

        int damage;
        int speed; // pixels per 10 seconds
        Coordinate position;
        std::vector<Coordinate>    path;

        static std::vector<EnemyInterceptor*>  interceptors;
        int pathI;
        static bool shipHit;
        int hitTimer;

    public:

        static Coordinate getPosition(int ship);

        static bool exitBattle();

};

#endif // ENEMYINTERCEPTOR_H_INCLUDED

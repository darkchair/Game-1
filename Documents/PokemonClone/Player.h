#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED


#include "Pokemon.h"

class Player {


    public:

        Player();

    public:

        std::vector<Pokemon*>    team;

        //Stats, preferences, etc.
        //Record record;

    public:

        int activePokemon;

        int chosenMove;

        int battlePhase;

        enum phases {

            chooseOption,
            chooseChoice

        };

        bool spikes;
        bool bomb;

        int  defenseBuff;


    public:

        Pokemon* getActivePokemon();

        Move* getMoveUsed();

        void setActivePokemon(int poke);

        void chooseMove();

        void incrementDefenseBuff();





};

//std::vector<Pokemon*>    team;

#endif // PLAYER_H_INCLUDED

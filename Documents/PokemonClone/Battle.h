#ifndef BATTLE_H_INCLUDED
#define BATTLE_H_INCLUDED

#include "Player.h"
#include "Pokemon.h"
#include "Moves.h"

class Battle {


    public:

        Battle(Player* play1, Player* play2);


    public:

        Pokemon* poke1;

        Pokemon* poke2;

        Player*  player1;

        Player*  player2;

        Move*   poke1Move;

        Move*   poke2Move;


        bool    twoVtwo;


        bool    battleSet;

        bool    player1Attack;
        bool    player2Attack;

        bool    poke1Knockout;
        bool    poke2Knockout;

        int     hitTimerPoke1;
        int     hitTimerPoke2;

        //Tracks how many pokemon aren't knocked out
        int     player1TeamCount;
        int     player2TeamCount;


        bool beatdown1On;
        bool beatdown2On;

        bool powerFlare1;
        bool powerFlare2;

        int bombDamage1;
        int bombDamage2;

        int parryDamage1;
        int parryDamage2;


    public:

        bool beginBattle();


        void planPlayer1();

        void planPlayer2();


        void executePokemon1();

        void executePokemon2();

        void executeSimultanious();



        int figureMod1(Pokemon* pokeT, int playerNumber);

        int figureDamage(int playerNumber);



};

#endif // BATTLE_H_INCLUDED

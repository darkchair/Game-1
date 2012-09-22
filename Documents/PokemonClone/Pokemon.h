#ifndef POKEMON_H_INCLUDED
#define POKEMON_H_INCLUDED

#include <SDL/SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Move.h"
#include "Moves.h"

class Pokemon {


    public:

        Pokemon();

        Pokemon(int element);

        Pokemon(int element, std::string name);

    public:

        std::string nickname;

        int level;

        int stamina;

        int maxStamina;

        int attack;

        int defense;

        int sattack;

        int sdefense;

        int speed;

        int criticalStage;

        int status;


        int element;






        bool sniper;

        bool burned;

        bool lightScreen;

        bool reflect;


        std::vector<Move*> pokeMoveSet;
        std::vector<int> elementChangeTracker;



    private:

        SDL_Surface*    pokemonImage;



    public:

        std::string getNickname();

        int getStamina();

        int getMaxStamina();

        int getAttack();

        int getDefense();

        int getSAttack();

        int getSDefense();

        int getSpeed();

        int getElement();

        int getStatus();

        void setStamina(int stam);

        void setStatus(int status);

        void addMove(Move* move);



        bool isCriticalHit();

        bool isSniper();

        bool isBurned();

        bool hasLightScreen();

        bool hasReflect();

        Move* getMove(int chosenMove);



        enum {

            martial = 0,
            mental,
            spirit,
            fire,
            water,
            wood,
            electric,
            ground,
            metal

        };




};

#endif // POKEMON_H_INCLUDED

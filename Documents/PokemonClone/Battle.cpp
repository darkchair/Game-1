#include "Battle.h"


Battle::Battle(Player* play1, Player* play2) {

    player1 = play1;

    player2 = play2;

    twoVtwo = false;

    battleSet = false;

    player1Attack = false;
    player2Attack = false;

    poke1Knockout = false;
    poke2Knockout = false;

    beatdown1On = false;
    beatdown2On = false;

    powerFlare1 = false;
    powerFlare2 = false;

    hitTimerPoke1 = 0;
    hitTimerPoke2 = 0;

    player1TeamCount = 3;
    player2TeamCount = 3;

    bombDamage1 = 0;
    bombDamage2 = 0;

    parryDamage1 = 0;
    parryDamage2 = 0;

}

bool Battle::beginBattle() {


    poke1 = player1->getActivePokemon();
    poke2 = player2->getActivePokemon();


    if(!beatdown2On)
        poke2Move = player2->getActivePokemon()->getMove( (rand()%4) );

    return true;




//Players assign plans

    //planPlayer1();

    //planPlayer2();






//Execute plans





}


void Battle::planPlayer1() {



    //Choose Action



    //Choose Move

    Battle::player1->chooseMove();



}

void Battle::planPlayer2() {


    //Choose Action



    //Choose Move

    Battle::player2->chooseMove();



}


void Battle::executePokemon1() {


    int attackStat = 0;
    int defenseAmount = 0;
    double mod1 = 0;
    int ch = 0;
    double mod2 = 0;
    int STAB = 1;

    if(player1Attack) {

        if(player2Attack) {
            if(poke2Move->getID() == 6) {
                poke1Move = poke1->getMove(rand() %4);
            }

            if(poke2Move->getID() == 9 && poke1->getElement()%3 == 1) {
                return;
            }
        }

        mod1 = figureMod1(poke1, 1);

        if(poke1->isCriticalHit()) {

            if(poke1->isSniper())
                ch = 3;
            else
                ch = 2;

        }
        else
            ch = 1;
        //STILL NEEDS IMPLEMENTATION
        mod2 = 1;

        if(poke1->getElement() == poke1Move->getElement())
            STAB = 2;

        hitTimerPoke2 = 600;
        //Using Bomb while there is another bomb means no damage  =(
        if(bombDamage2 != 0) {
            poke2->setStamina(poke2->getStamina() - bombDamage1);
            bombDamage2 = 0;
            player2->bomb = false;
        }
        if(poke1Move->getID() != 14)
            poke2->setStamina(poke2->getStamina() - figureDamage(1));
        else //If poke1 uses Power Bomb
            bombDamage2 = figureDamage(1);
        if(poke2->getStatus() == 1)//If poke2 is poisoned
            poke2->setStamina(poke2->getStamina() - 20);
        if(player2->spikes)//If player2 has spikes on their field
            poke2->setStamina(poke2->getStamina() - 12);

        if(player2->getActivePokemon()->getStamina() <= 0) {//poke2?
            poke2Knockout = true;
            player2TeamCount--;
        }

    }

//    double damage = ((((((((poke1.getLevel() × 2 ÷ 5) + 2) × currentMove.getBaseP() × attackStat ÷ 50) ÷ defenseAmount) × mod1) + 2) × ch × mod2 × R ÷ 100) × STAB × Type1 × Type2 × Mod3);
 //   double damage = (((((((1 × currentMove.getBaseP() × attackStat ÷ 50) ÷ defenseAmount) × mod1) + 2) × ch × mod2 × 1 ÷ 100) × STAB × Type1 × Type2 × Mod3);
    //int damage = (1*poke1Move->getBaseP() / 2) * STAB;




}


void Battle::executePokemon2() {

    int attackStat = 0;
    int defenseAmount = 0;
    double mod1 = 0;
    int ch = 0;
    double mod2 = 0;

    if(player2Attack) {

        if(player1Attack) {
            if(poke1Move->getID() == 9 && poke2->getElement()%3 == 1) {
                return;
            }
        }

        mod1 = figureMod1(poke2, 2);

        if(poke2->isCriticalHit()) {

            if(poke2->isSniper())
                ch = 3;
            else
                ch = 2;

        }
        else
            ch = 1;
        //STILL NEEDS IMPLEMENTATION
        mod2 = 1;

        hitTimerPoke1 = 600;

        if(bombDamage1 != 0) {
            poke1->setStamina(poke1->getStamina() - bombDamage1);
            bombDamage1 = 0;
            player1->bomb = false;
        }
        if(poke2Move->getID() != 14)
            poke1->setStamina(poke1->getStamina() - figureDamage(2));
        else//If poke2 uses Power Bomb
            bombDamage1 = figureDamage(2);
        if(poke1->getStatus() == 1)//If poke1 is poisoned
            poke1->setStamina(poke1->getStamina() - 20);
        if(player1->spikes)//If player1 has spikes on their field
            poke1->setStamina(poke1->getStamina() - 12);

        if(player1->getActivePokemon()->getStamina() <= 0) {//poke1?
            poke1Knockout = true;
            player1TeamCount--;
        }



    }

//    double damage = ((((((((poke1.getLevel() × 2 ÷ 5) + 2) × currentMove.getBaseP() × attackStat ÷ 50) ÷ defenseAmount) × mod1) + 2) × ch × mod2 × R ÷ 100) × STAB × Type1 × Type2 × Mod3);





}

void Battle::executeSimultanious() {

    int attackStat = 0;
    int defenseAmount = 0;
    double mod1 = 0;
    int ch = 0;
    double mod2 = 0;

    if(player1Attack && !(poke1->getElement()%3 == 1 && poke2Move->getID() == 9)) {


        mod1 = figureMod1(poke1, 1);

        if(poke1->isCriticalHit()) {

            if(poke1->isSniper())
                ch = 3;
            else
                ch = 2;

        }
        else
            ch = 1;
        //STILL NEEDS IMPLEMENTATION
        mod2 = 1;

        hitTimerPoke2 = 600;

        if(bombDamage2 != 0) {
            poke2->setStamina(poke2->getStamina() - bombDamage1);
            bombDamage2 = 0;
            player2->bomb = false;
        }
        if(poke1Move->getID() != 14)
            poke2->setStamina(poke2->getStamina() - figureDamage(1));
        else //If poke1 uses Power Bomb
            bombDamage2 = figureDamage(1);
        if(poke2->getStatus() == 1)//If poke2 is poisoned
            poke2->setStamina(poke2->getStamina() - 20);
        if(player2->spikes)//If player2 has spikes on their field
            poke2->setStamina(poke2->getStamina() - 12);

        if(player2->getActivePokemon()->getStamina() <= 0) {//poke2?
            poke2Knockout = true;
            player2TeamCount--;
        }

    }

    if(player2Attack && !(poke2->getElement()%3 == 1 && poke1Move->getID() == 9)) {


        mod1 = figureMod1(poke2, 2);

        if(poke2->isCriticalHit()) {

            if(poke2->isSniper())
                ch = 3;
            else
                ch = 2;

        }
        else
            ch = 1;
        //STILL NEEDS IMPLEMENTATION
        mod2 = 1;

        hitTimerPoke1 = 600;

        if(bombDamage1 != 0) {
            poke1->setStamina(poke1->getStamina() - bombDamage1);
            bombDamage1 = 0;
            player1->bomb = false;
        }
        if(poke2Move->getID() != 14)
            poke1->setStamina(poke1->getStamina() - figureDamage(2));
        else//If poke2 uses Power Bomb
            bombDamage1 = figureDamage(2);
        if(poke1->getStatus() == 1)//If poke1 is poisoned
            poke1->setStamina(poke1->getStamina() - 20);
        if(player1->spikes)//If player1 has spikes on their field
            poke1->setStamina(poke1->getStamina() - 12);

        if(player1->getActivePokemon()->getStamina() <= 0) {//poke1?
            poke1Knockout = true;
            player1TeamCount--;
        }


    }








}




int Battle::figureMod1(Pokemon* pokeT, int playerNumber) {

    double brn = 0, rl = 0, tvt = 0, sd = 0, ff = 0;

    if(pokeT->isBurned())
        brn = .5;

    Move* currentMove;
    if(playerNumber == 1)
        currentMove = poke1Move;
    if(playerNumber == 2)
        currentMove = poke2Move;

    if(currentMove->isSpecialAttack()) {
        if(pokeT->hasLightScreen()) {

            if(Battle::twoVtwo)
                rl = .6666;
            else
                rl = .5;

        }
    }
    else if(pokeT->hasReflect()) {

        if(twoVtwo)
            rl = .6666;
        else
            rl = .5;

    }
    else
        rl = 1;



    if(currentMove->isHitsMultiple()) {

        if(twoVtwo)
            tvt = .75;

    }
    //STILL NEEDS IMPLEMENTATION
    sd = 1;
    //STILL NEEDS IMPLEMENTATION
    ff = 1;

    return brn*rl*tvt*sd*ff;

}

int Battle::figureDamage(int playerNumber) {

    Pokemon* activePoke;
    Pokemon* opposingPoke;
    Move*    activeMove;
    Move*    reactiveMove;
    int damage;

    if(playerNumber == 1) {
        activePoke = poke1;
        opposingPoke = poke2;
        activeMove = poke1Move;
        reactiveMove = poke2Move;
    }
    else {
        activePoke = poke2;
        opposingPoke = poke1;
        activeMove = poke2Move;
        reactiveMove = poke1Move;
    }
    //Multiplier relative to a regular attack
    double modif = (double)activeMove->getPower() / 10;
    if(playerNumber == 1) {
        if(activeMove->getID() == 26 && player2Attack)
            modif = (double)3 / 10;
    }
    else {
        if(activeMove->getID() == 26 && player1Attack)
            modif = (double)3 / 10;
    }


    //If opponent is Offensive type
    if((opposingPoke->getElement())%3 == 0){

        //If hitting with a Support move
        if((activeMove->getElement())%3 == 1) {

            //If STAB applies
            if(activePoke->getElement() == activeMove->getElement())
                damage = 34*modif;
            else
                damage = 28*modif;

            if(reactiveMove != NULL) {

                if(reactiveMove->getID() == 1)
                    damage = damage/2;

                if(reactiveMove->getID() == 17)
                    damage = 0;

            }

        }
        //If hitting with an Offensive move
        if((activeMove->getElement())%3 == 0) {

            //If STAB applies
            if(activePoke->getElement() == activeMove->getElement())
                damage = 35*modif;
            else
                damage = 27*modif;

            if(reactiveMove != NULL) {

                if(reactiveMove->getID() == 8)
                    damage = damage/2;

                if(reactiveMove->getID() == 17)
                    damage = 0;
            }

        }
        //If hitting with a Defensive Move
        if((activeMove->getElement())%3 == 2) {

            //If STAB applies
            if(activePoke->getElement() == activeMove->getElement())
                damage = 26*modif;
            else
                damage = 21*modif;

            if(reactiveMove != NULL) {

                if(reactiveMove->getID() == 5)
                    damage = damage/2;

                if(reactiveMove->getID() == 13)
                    damage = 0;

            }

        }

    }
    //If opponent is Support type
    if((opposingPoke->getElement())%3 == 1) {

        //If hitting with a Defensive Move
        if((activeMove->getElement())%3 == 2) {

            //If STAB applies
            if(activePoke->getElement() == activeMove->getElement())
                damage = 73*modif;
            //Else if you are a different kind of Defensive pokemon
            else if (activePoke->getElement()%3 == 2)
                damage = 58*modif;
            else
                damage = 40*modif;

            if(reactiveMove != NULL) {

                if(reactiveMove->getID() == 5)
                    damage = damage/2;

                if(reactiveMove->getID() == 13)
                    damage = 0;

            }

        }
        //If hitting with a Support move
        if((activeMove->getElement())%3 == 1) {

            //If STAB applies
            if(activePoke->getElement() == activeMove->getElement())
                damage = 22*modif;
            else
                damage = 15*modif;

            if(reactiveMove != NULL) {

                if(reactiveMove->getID() == 1)
                    damage = damage/2;

                if(reactiveMove->getID() == 21)
                    damage = 0;

            }

        }
        //If hitting with an Offensive move
        if((activeMove->getElement())%3 == 0) {

            //If STAB applies
            if(activePoke->getElement() == activeMove->getElement())
                damage = 27*modif;
            else
                damage = 20*modif;

            if(reactiveMove != NULL) {

                if(reactiveMove->getID() == 8)
                    damage = damage/2;

                if(reactiveMove->getID() == 17)
                    damage = 0;
            }

        }

    }
    //If opponent is Defensive type
    if((opposingPoke->getElement())%3 == 2) {

        //If hitting with an Offensive move
        if((activeMove->getElement())%3 == 0) {

            //If STAB applies
            if(activePoke->getElement() == activeMove->getElement())
                damage = 59*modif;
            else
                damage = 49*modif;

            if(reactiveMove != NULL) {

                if(reactiveMove->getID() == 8)
                    damage = damage/2;

                if(reactiveMove->getID() == 17)
                    damage = 0;

            }

        }
        //If hitting with a Defensive Move -?????????????????????????????????????????????????????????????????-
        if((activeMove->getElement())%3 == 2) {

            //If STAB applies
            if(activePoke->getElement() == activeMove->getElement())
                damage = 41*modif;
            else
                damage = 34*modif;

            if(reactiveMove != NULL) {

                if(reactiveMove->getID() == 5)
                    damage = damage/2;

                if(reactiveMove->getID() == 13)
                    damage = 0;

            }

        }
        //If hitting with a Support move
        if((activeMove->getElement())%3 == 1) {

            //If STAB applies
            if(activePoke->getElement() == activeMove->getElement())
                damage = 16*modif;
            else
                damage = 12*modif;

            if(reactiveMove != NULL) {

                if(reactiveMove->getID() == 1)
                    damage = damage/2;

                if(reactiveMove->getID() == 17)
                    damage = 0;

            }

        }

    }

    if(playerNumber == 1) {
        damage = damage * (100 - player2->defenseBuff)/100;
        if(poke2Move->getID() == 32)
            damage = damage/2;
    }
    if(playerNumber == 2) {
        damage = damage * (100 - player1->defenseBuff)/100;
        if(poke1Move->getID() == 32)
            damage = damage/2;
    }

    return damage;



}

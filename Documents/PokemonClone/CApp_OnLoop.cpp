#include "CApp.h"

void CApp::OnLoop() {

    if(player1Ready && !setBattleOff) {

        currentBattle->battleSet = true;

        waitingForKnockoutSwitch = false;//Why?
        currentBattle->poke1Knockout = false;
        currentBattle->poke2Knockout = false;
        //setBattleOff = false;

        hitByMessagePoke1.CurrentFrame = 0;
        hitByMessagePoke2.CurrentFrame = 0;
    }

    if(currentBattle->battleSet) {

        if(currentBattle->powerFlare2) {
            currentBattle->player2Attack = false;
            currentBattle->powerFlare2 = false;
        }
        else
            currentBattle->player2Attack = true;


        currentBattle->beginBattle();


        if(currentBattle->poke1Move->getID() == 18){
            currentBattle->bombDamage1 = 0;
            currentBattle->player1->bomb = false;
            currentBattle->player1->spikes = false;
            currentBattle->poke1->status = 0;
        }
        if(currentBattle->poke2Move->getID() == 18){
            currentBattle->bombDamage2 = 0;
            currentBattle->player2->bomb = false;
            currentBattle->player2->spikes = false;
            currentBattle->poke2->status = 0;
        }

        if(!currentBattle->player1Attack && !currentBattle->player2Attack) {
            //Do Nothing
        }
        else if(!currentBattle->player1Attack)  {
            if(!currentBattle->poke2Knockout) {//poke2?
                currentBattle->executePokemon2();
            }
        }
        else if(!currentBattle->player2Attack) {
            if(!currentBattle->poke1Knockout) {//poke1?
                currentBattle->executePokemon1();
            }
        }
        else if(currentBattle->poke1Move->getPriorityLevel() < currentBattle->poke2Move->getPriorityLevel()) {
            currentBattle->executePokemon1();
            if(!currentBattle->poke2Knockout) {//poke2?
                if(currentBattle->poke2Move->getID() == 18){
                    currentBattle->bombDamage2 = 0;
                    currentBattle->player2->bomb = false;
                    currentBattle->player2->spikes = false;
                    currentBattle->poke2->status = 0;
                }
                if(!(currentBattle->poke2->getElement()%3 == 1 && currentBattle->poke1Move->getID() == 9)) {
                    currentBattle->executePokemon2();
                }
            }
        }
        else if(currentBattle->poke2Move->getPriorityLevel() < currentBattle->poke1Move->getPriorityLevel()) {
            currentBattle->executePokemon2();
            if(!currentBattle->poke1Knockout) {//poke1?
                if(currentBattle->poke2Move->getID() == 6){
                    currentBattle->poke1Move = player1->getActivePokemon()->getMove(rand() % 4);
                }
                if(!(currentBattle->poke1->getElement()%3 == 1 && currentBattle->poke2Move->getID() == 9)) {
                    currentBattle->executePokemon1();
                }
            }
        }
        else {
            currentBattle->executeSimultanious();
        }




        if(currentBattle->player1Attack) {
            //Adjust Element Player 1
            if(currentBattle->poke1->elementChangeTracker.at(currentBattle->poke1Move->getElement()) < 2 && currentBattle->poke1Move->getElement() != currentBattle->poke1->element) {
                currentBattle->poke1->elementChangeTracker.at(currentBattle->poke1Move->getElement())++;
                if(currentBattle->poke1->elementChangeTracker.at(currentBattle->poke1Move->getElement()) == 2) {
                    currentBattle->poke1->element = currentBattle->poke1Move->getElement();
                    currentBattle->poke1->elementChangeTracker.at(currentBattle->poke1Move->getElement()) = 0;
                }
            }
            hitByTimerPoke2 = 600;
        }

        if(currentBattle->player2Attack) {
            //Adjust Element Player 2
            if(currentBattle->poke2->elementChangeTracker.at(currentBattle->poke2Move->getElement()) < 2 && currentBattle->poke2Move->getElement() != currentBattle->poke2->element) {
                currentBattle->poke2->elementChangeTracker.at(currentBattle->poke2Move->getElement())++;
                if(currentBattle->poke2->elementChangeTracker.at(currentBattle->poke2Move->getElement()) == 2) {
                    currentBattle->poke2->element = currentBattle->poke2Move->getElement();
                    currentBattle->poke2->elementChangeTracker.at(currentBattle->poke2Move->getElement()) = 0;
                }
            }
            hitByTimerPoke1 = 600;
        }

        currentBattle->battleSet = false;
        player1Ready = false;

        if(currentBattle->poke1Knockout == true) {
            waitingForKnockoutSwitch = true;
            currentBattle->beatdown1On = false;
        }
        else {
            if(currentBattle->player2Attack) {

                if(currentBattle->poke2Move->getID() == 0)
                    bounceBackSwitch = true;

                if(currentBattle->poke2Move->getID() == 2)
                    currentBattle->beatdown2On = true;

                if(currentBattle->poke2Move->getID() == 4)
                    currentBattle->poke1->setStatus(1);

                if(currentBattle->poke2Move->getID() == 12)
                    currentBattle->powerFlare2 = true;

         /*       if(currentBattle->poke2Move->getID() == 14) {
                    if(currentBattle->poke2->getElement() % 3 == 0)
                        currentBattle->player1->bomb = 2;
                    else
                        currentBattle->player1->bomb = 1;
                }*/
                if(currentBattle->poke2Move->getID() == 20)
                    currentBattle->player2->incrementDefenseBuff();

                if(currentBattle->poke2Move->getID() == 28)
                    currentBattle->player1->spikes = true;

            }

        }



        if(currentBattle->poke2Knockout == true && currentBattle->player2TeamCount != 0){
            if(knockoutTimer2 == 0) {
                animateKnockoutBool = true;
                //Randomly switch to another available pokemon
                do{

                    currentBattle->player2->setActivePokemon(rand() % 3);

                }while(currentBattle->player2->getActivePokemon()->getStamina() <= 0);
                currentBattle->beatdown2On = false;
            }

        }
        else {
            if(currentBattle->player1Attack) {
                if(currentBattle->poke1Move->getID() == 0) {
                    if(knockoutTimer2 == 0) {
                        //Randomly switch to another available pokemon
                        do{

                            currentBattle->player2->setActivePokemon(rand() % 3);

                        }while(currentBattle->player2->getActivePokemon()->getStamina() <= 0);
                    }
                }
            }
            if(currentBattle->player1Attack) {
                if(currentBattle->poke1Move->getID() == 2)
                    currentBattle->beatdown1On = true;

                if(currentBattle->poke1Move->getID() == 4)
                    currentBattle->poke2->setStatus(1);

                if(currentBattle->poke1Move->getID() == 12)
                    currentBattle->powerFlare1 = true;

                if(currentBattle->poke1Move->getID() == 14) {
                    if(currentBattle->poke1->getElement() % 3 == 0)
                        currentBattle->player2->bomb = 2;
                    else
                        currentBattle->player2->bomb = 1;
                }

                if(currentBattle->poke1Move->getID() == 20)
                    currentBattle->player1->incrementDefenseBuff();

                if(currentBattle->poke1Move->getID() == 28)
                    currentBattle->player2->spikes = true;
            }
        }



    }

    if((currentBattle->player2TeamCount == 0 || currentBattle->player1TeamCount == 0) && !state_welcomeScreen) {

        if(currentBattle->hitTimerPoke1 == 0 && knockoutTimer1 == 0 && currentBattle->hitTimerPoke2 == 0 && knockoutTimer2 == 0) {
            if(currentBattle->player2TeamCount == 0 /*&& winMessageDelay == 0*/) {
                state_player1Win = true;
                //winMessageDelay = 400;
            }
            if(currentBattle->player1TeamCount == 0 /*&& winMessageDelay == 0*/) {
                state_player2Win = true;
                //winMessageDelay = 400;
            }
            //winMessageDelay--;
        }

    }

}

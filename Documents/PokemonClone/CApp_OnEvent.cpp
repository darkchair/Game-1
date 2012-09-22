#include "CApp.h"

void CApp::OnEvent(SDL_Event* Event) {
    CEvent::OnEvent(Event);
}

void CApp::OnExit() {
    Running = false;
}

void CApp::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {

    locX = mX;
    locY = mY;

    /*if(hoveredElement == findElement(mX, mY))
        hoveredElementTooltipTimer++;
    else {
        hoveredElement = findElement(mX, mY);
        hoveredElementTooltipTimer = 0;
    }*/

}

void CApp::OnLButtonDown(int mX, int mY) {

    if(state_helpScreen) {

        state_helpScreen = false;
        state_welcomeScreen = true;

    }
    if(state_welcomeScreen) {

        welcomeScreenLogic(mX, mY);

    }
    else if(state_storyScreen) {

        state_storyScreen = false;
        state_welcomeScreen = true;

    }
    else if(state_selectElement1) {

        int chosenElement = findElement(mX, mY);
        if(chosenElement != -1) {
            state_selectElement1 = false;
            state_selectElement2 = true;

            addPokemon(chosenElement, "Pokemon 1");
        }

    }
    else if(state_selectElement2) {

        int chosenElement = findElement(mX, mY);
        if(chosenElement != -1) {
            state_selectElement2 = false;
            state_selectElement3 = true;

            addPokemon(chosenElement, "Pokemon 2");
        }

    }
    else if(state_selectElement3) {

        int chosenElement = findElement(mX, mY);
        if(chosenElement != -1) {
            state_selectElement3 = false;
            state_selectMoves1 = true;

            addPokemon(chosenElement, "Pokemon 3");
        }

    }
    else if(state_selectMoves1) {

        if(state_elementSelected) {
            chosenMove = findMove(mX, mY, chosenMoveElement);
            if(chosenMove != -1) {// && chosenMove >= 0 && chosenMove <= 35
                if(addMove(chosenMove, 0)) { //If the poke now has 4 moves
                    state_selectMoves1 = false;
                    state_selectMoves2 = true;
                    state_elementSelected = false;
                    state_selectTheMove = -1;

                    player2->team.at(0)->pokeMoveSet.push_back(new Move());
                    player2->team.at(0)->pokeMoveSet.push_back(new Move());
                    player2->team.at(0)->pokeMoveSet.push_back(new Move());
                    player2->team.at(0)->pokeMoveSet.push_back(new Move());
                }
                else {
                    state_elementSelected = false;
                    state_selectTheMove = -1;
                }

            }
            else {
                state_elementSelected = false;
                state_selectTheMove = -1;
            }
        }
        else {
            chosenMoveElement = findMoveElement(mX, mY);
            if(chosenMoveElement != -1)
                state_elementSelected = true;
        }

    }
    else if(state_selectMoves2) {

        if(state_elementSelected) {
            chosenMove = findMove(mX, mY, chosenMoveElement);
            if(chosenMove != -1) {// && chosenMove >= 0 && chosenMove <= 35
                if(addMove(chosenMove, 1)) { //If the poke now has 4 moves
                    state_selectMoves2 = false;
                    state_selectMoves3 = true;
                    state_elementSelected = false;
                    state_selectTheMove = -1;

                    player2->team.at(1)->pokeMoveSet.push_back(new Move());
                    player2->team.at(1)->pokeMoveSet.push_back(new Move());
                    player2->team.at(1)->pokeMoveSet.push_back(new Move());
                    player2->team.at(1)->pokeMoveSet.push_back(new Move());
                }
                else {
                    state_elementSelected = false;
                    state_selectTheMove = -1;
                }

            }
            else {
                state_elementSelected = false;
                state_selectTheMove = -1;
            }
        }
        else {
            chosenMoveElement = findMoveElement(mX, mY);
            if(chosenMoveElement != -1)
                state_elementSelected = true;
        }

    }
    else if(state_selectMoves3) {

        if(state_elementSelected) {
            chosenMove = findMove(mX, mY, chosenMoveElement);
            if(chosenMove != -1) {// && chosenMove >= 0 && chosenMove <= 35
                if(addMove(chosenMove, 2)) { //If the poke now has 4 moves
                    state_selectMoves3 = false;
                    state_elementSelected = false;
                    state_selectTheMove = -1;

                    player2->team.at(2)->pokeMoveSet.push_back(new Move());
                    player2->team.at(2)->pokeMoveSet.push_back(new Move());
                    player2->team.at(2)->pokeMoveSet.push_back(new Move());
                    player2->team.at(2)->pokeMoveSet.push_back(new Move());
                }
                else {
                    state_elementSelected = false;
                    state_selectTheMove = -1;
                }

            }
            else {
                state_elementSelected = false;
                state_selectTheMove = -1;
            }
        }
        else {
            chosenMoveElement = findMoveElement(mX, mY);
            if(chosenMoveElement != -1)
                state_elementSelected = true;
        }

    }
    else if(state_player1Win) {

        state_welcomeScreen = true;
        state_selectElement1 = false;
        state_selectElement2 = false;
        state_selectElement3 = false;
        state_moveOverlay = false;
        state_switchPokemon = false;
        state_player1Win = false;
        state_player2Win = false;

    }
    else if(state_player2Win) {

        state_welcomeScreen = true;
        state_selectElement1 = false;
        state_selectElement2 = false;
        state_selectElement3 = false;
        state_moveOverlay = false;
        state_switchPokemon = false;
        state_player1Win = false;
        state_player2Win = false;

    }

    else {//Battle State

/*        if(currentBattle->poke1->taunted) { //Not needed yet as CPU is already random
            currentBattle->poke1Move = currentBattle->poke1->getMove(rand() % 4);
            currentBattle->player1Attack = true;
            player1Ready = true;
            setBattleOff = false;
            return;
        }//Does being taunted or beatdown take priority?*/
        if(currentBattle->beatdown1On) {
            currentBattle->player1Attack = true;
            player1Ready = true;
            setBattleOff = false;
            return;
        }

        if(currentBattle->powerFlare1) {
            currentBattle->player1Attack = false;
            player1Ready = true;
            setBattleOff = false;
            currentBattle->powerFlare1 = false;
            return;
        }

        if(state_switchPokemon == true) {
            setBattleOff = false;

            if(waitingForKnockoutSwitch) {
            //Have to check if pokemon were knocked out before the rest of the checks, as the future checks will modify the values
                setBattleOff = true;

            }

            switchPokemonLogic(mX, mY);
        }

        else if(state_moveOverlay == true) {
            moveOverlayLogic(mX, mY);
        }

        if( atInitiateLocation(mX, mY) && hitByTimerPoke1 == 0 && hitByTimerPoke2 == 0) {
            state_moveOverlay = true;
        }
        else {
            state_moveOverlay = false;
        }

    }


}

bool CApp::atInitiateLocation(int mX, int mY) {
    //If click is within bounds of initiate button
    if(mX <= 119 && mY >= 507) {

        return true;

    }
    else
        return false;

}

int CApp::findElement(int mX, int mY) {

    //Location relative to selection screen
    //Martial
    if(mY >= 200 && mX >= 241 && mY <= 255 && mX <= 309)
        return 0;
    //Mental
    if(mY >= 200 && mX >= 389 && mY <= 255 && mX <= 459)
        return 1;
    //Spirit
    if(mY >= 109 && mX >= 318 && mY <= 159 && mX <= 386)
        return 2;
    //Fire
    if(mY >= 459 && mX >= 448 && mY <= 515 && mX <= 520)
        return 3;
    //Water
    if(mY >= 459 && mX >= 593 && mY <= 515 && mX <= 662)
        return 4;
    //Wood
    if(mY >= 367 && mX >= 519 && mY <= 418 && mX <= 590)
        return 5;
    //Electric
    if(mY >= 458 && mX >= 45 && mY <= 514 && mX <= 116)
        return 6;
    //Ground
    if(mY >= 458 && mX >= 196 && mY <= 512 && mX <= 264)
        return 7;
    //Metal
    if(mY >= 369 && mX >= 125 && mY <= 420 && mX <= 190)
        return 8;

    return -1;

}

int CApp::findMoveElement(int mX, int mY) {

    if(mY >= 24 && mX >= 26 && mY <= 76 && mX <= 93) {
        state_selectTheMove = 0;
        return 0;
    }
    if(mY >= 85 && mX >= 26 && mY <= 138 && mX <= 93) {
        state_selectTheMove = 1;
        return 1;
    }
    if(mY >= 148 && mX >= 26 && mY <= 200 && mX <= 93) {
        state_selectTheMove = 2;
        return 2;
    }
    if(mY >= 213 && mX >= 26 && mY <= 263 && mX <= 93) {
        state_selectTheMove = 3;
        return 3;
    }
    if(mY >= 273 && mX >= 26 && mY <= 325 && mX <= 93) {
        state_selectTheMove = 4;
        return 4;
    }
    if(mY >= 332 && mX >= 26 && mY <= 383 && mX <= 93) {
        state_selectTheMove = 5;
        return 5;
    }
    if(mY >= 395 && mX >= 26 && mY <= 448 && mX <= 93) {
        state_selectTheMove = 6;
        return 6;
    }
    if(mY >= 458 && mX >= 26 && mY <= 510 && mX <= 93) {
        state_selectTheMove = 7;
        return 7;
    }
    if(mY >= 518 && mX >= 26 && mY <= 570 && mX <= 93) {
        state_selectTheMove = 8;
        return 8;
    }
    if(mY >= 550 && mX >= 600 && mY <= 586 && mX <= 665) { //Random
        state_selectTheMove = 9;
        return 9;
    }

    state_selectTheMove = -1;
    return -1;

}

int CApp::findMove(int mX, int mY, int chosenMoveElement) {

    if(chosenMoveElement == 9)
        return 99;
    if(mY >= 70 && mX >= 150 && mY <= 70+225 && mX <= 150+225)
        return (4*chosenMoveElement) + 0;
    if(mY >= 70 && mX >= 420 && mY <= 70+225 && mX <= 420+225)
        return (4*chosenMoveElement) + 1;
    if(mY >= 320 && mX >= 150 && mY <= 320+225 && mX <= 150+225)
        return (4*chosenMoveElement) + 2;
    if(mY >= 320 && mX >= 420 && mY <= 320+225 && mX <= 420+225)
        return (4*chosenMoveElement) + 3;

    return -1;

}

void CApp::welcomeScreenLogic(int mX, int mY) {

    if(mX >= 36 && mY >= 342 && mX <= 241 && mY <= 487) {
        //If Start is clicked
        player1 = new Player();
        player2 = new Player();
        currentBattle = new Battle(player1, player2);

        state_welcomeScreen = false;
        state_selectElement1 = true;

    }

    if(mX >= 459 && mY >= 342 && mX <= 664 && mY <= 487) {
        //If Help is clicked
        state_welcomeScreen = false;
        state_helpScreen = true;

    }

    if(mX >= 227 && mY >= 527 && mX <= 473 && mY <= 600) {
        //If Story is clicked
        state_welcomeScreen = false;
        state_storyScreen = true;

    }

}

void CApp::addPokemon(int chosenElement, std::string name) {

    Pokemon* chosenPokemon = new Pokemon(chosenElement, name);
    currentBattle->player1->team.push_back(chosenPokemon);

    int randomElement = rand() % 9;
    Pokemon* randPokemon = new Pokemon(randomElement);
    currentBattle->player2->team.push_back(randPokemon);
    //std::cout << (int)currentBattle->player2->team.size();    //Doesn't Work?

}

bool CApp::addMove(int chosenMove, int poke) {

    if(chosenMove == 99) { // If select random, randomize all moves for the poke
        Move* move = new Move();
        currentBattle->player1->team.at(poke)->addMove(move);
        move = new Move();
        currentBattle->player1->team.at(poke)->addMove(move);
        move = new Move();
        currentBattle->player1->team.at(poke)->addMove(move);
        move = new Move();
        currentBattle->player1->team.at(poke)->addMove(move);

        return true;
    }

    Move* move = new Move(chosenMove);
    currentBattle->player1->team.at(poke)->addMove(move);
    if(currentBattle->player1->team.at(poke)->pokeMoveSet.size() == 4)
        return true;
    else
        return false;

}

void CApp::switchPokemonLogic(int mX, int mY) {

    if(mX >= 245+30 && mY >= 150+100 && mX <= 380+30 && mY <= 240+100) {
                state_switchPokemon = false;
                state_moveOverlay = true;
    }
    else if(mX >= 235+30 && mY >= 22+100 && mX <= 387+30 && mY <= 122+100) {

        if(currentBattle->player1->activePokemon == 0) {

            //Pokemon already out
            state_switchPokemon = false;

        }
        else {
            if(currentBattle->player1->team.at(0)->getStamina() > 0) {
                currentBattle->player1->setActivePokemon(0);
                state_switchPokemon = false;
                currentBattle->player1Attack = false;
                currentBattle->poke1Knockout = false;
                if(!bounceBackSwitch) {
                    waitingForKnockoutSwitch = false;
                    player1Ready = true;
                }
                else {
                    bounceBackSwitch = false;
                }
            }
            else {
                //Can't choose knocked out pokemon
            }
        }

    }
    else if(mX >= 65+30 && mY >= 271+100 && mX <= 209+30 && mY <= 373+100) {

        if(currentBattle->player1->activePokemon == 1) {

            //Pokemon already out

        }
        else {
            if(currentBattle->player1->team.at(1)->getStamina() > 0) {
                currentBattle->player1->setActivePokemon(1);
                state_switchPokemon = false;
                currentBattle->player1Attack = false;
                player1Ready = true;
                currentBattle->poke1Knockout = false;
                waitingForKnockoutSwitch = false;
            }
            else {
                //Can't choose knocked out pokemon
            }
        }

    }
    else if(mX >= 421+30 && mY >= 271+100 && mX <= 564+30 && mY <= 372+100) {

        if(currentBattle->player1->activePokemon == 2) {

            //Pokemon already out

        }
        else {
            if(currentBattle->player1->team.at(2)->getStamina() > 0) {
                currentBattle->player1->setActivePokemon(2);
                state_switchPokemon = false;
                currentBattle->player1Attack = false;
                player1Ready = true;
                currentBattle->poke1Knockout = false;
                waitingForKnockoutSwitch = false;
            }
            else {
                //Can't choose knocked out pokemon
            }
        }

    }
    else {

        //Do nothing

    }

}

void CApp::moveOverlayLogic(int mX, int mY) {

    if(mX >= 0+30 && mY >= 0+100 && mX <= 270+30 && mY <= 140+100) {
        currentBattle->poke1Move = player1->getActivePokemon()->getMove(0);
        currentBattle->player1Attack = true;
        player1Ready = true;
        setBattleOff = false;
    }
    if(mX >= 360+30 && mY >= 0+100 && mX <= 640+30 && mY <= 140+100) {
        currentBattle->poke1Move = player1->getActivePokemon()->getMove(1);
        currentBattle->player1Attack = true;
        player1Ready = true;
        waitingForKnockoutSwitch = false;
        setBattleOff = false;
    }
    if(mX >= 0+30 && mY >= 250+100 && mX <= 270+30 && mY <= 400+100) {
        currentBattle->poke1Move = player1->getActivePokemon()->getMove(2);
        currentBattle->player1Attack = true;
        player1Ready = true;
        waitingForKnockoutSwitch = false;
        setBattleOff = false;
    }
        //currentBattle->player1->setActivePokemon(0);
                        //state_switchPokemon = false;
                        //currentBattle->player1Attack = false;
                        //player1Ready = true;
                        //currentBattle->poke1Knockout = false;
                        //waitingForKnockoutSwitch = false;
    if(mX >= 360+30 && mY >= 250+100 && mX <= 640+30 && mY <= 400+100) {
        currentBattle->poke1Move = player1->getActivePokemon()->getMove(3);
        currentBattle->player1Attack = true;
        player1Ready = true;
        waitingForKnockoutSwitch = false;
        setBattleOff = false;
    }
    if(mX >= 245+30 && mY >= 150+100 && mX <= 380+30 && mY <= 240+100) {
        state_switchPokemon = true;
        state_moveOverlay = false;
        waitingForKnockoutSwitch = false;
    }

}

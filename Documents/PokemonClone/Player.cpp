#include "Player.h"




Player::Player() {

    //team.resize(0);
    activePokemon = 0;
    spikes = false;
    bomb = false;
    defenseBuff = 0;

}


Pokemon* Player::getActivePokemon() {

    return team.at(activePokemon);

}


Move* Player::getMoveUsed() {

    return team.at(activePokemon)->getMove(chosenMove);

}

void Player::setActivePokemon(int poke) {

    activePokemon = poke;

}

void Player::chooseMove() {

    //Ask for move
    int desiredMove = -1;

    //Put it in a variable
    chosenMove = desiredMove;

}

void Player::incrementDefenseBuff() {

    if(defenseBuff == 0) {
        defenseBuff = 20;
        return;
    }
    if(defenseBuff == 20) {
        defenseBuff = 30;
        return;
    }
    if(defenseBuff == 30) {
        defenseBuff = 40;
        return;
    }
    if(defenseBuff == 40) {
        defenseBuff = 45;
        return;
    }
    if(defenseBuff == 45) {
        defenseBuff = 50;
        return;
    }

}

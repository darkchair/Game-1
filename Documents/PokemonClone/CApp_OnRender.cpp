#include "CApp.h"


void CApp::OnRender() {

    if(state_welcomeScreen) {
        //display Welcome Screen
        CSurface::OnDraw(Surf_Display, Surf_WelcomeScreen, 0, 0);
    }

    else if(state_helpScreen) {
        //display Help Screen
        CSurface::OnDraw(Surf_Display, Surf_HelpScreen, 0, 0);
    }

    else if(state_storyScreen) {
        CSurface::OnDraw(Surf_Display, Surf_DialogBackground, 0, 0);
        CSurface::OnDraw(Surf_Display, Surf_DialogBackgroundBox, 0, 350);
        textColor = { 255, 255, 255 };
        Surf_TextHolder = TTF_RenderText_Blended( font18, "This is a story.", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 40, 380);
        SDL_FreeSurface(Surf_TextHolder);
        textColor = { 0, 0, 0 };
    }

    else if(state_selectElement1) {

        displaySelectElement(1);
    }
    else if(state_selectElement2) {

        displaySelectElement(2);
    }
    else if(state_selectElement3) {

        displaySelectElement(3);
    }

    else if(state_selectMoves1) {

        displaySelectMoves(0);
    }

    else if(state_selectMoves2) {

        displaySelectMoves(1);
    }

    else if(state_selectMoves3) {

        displaySelectMoves(2);
    }

    else {
        //display Battle
        displayBattle();

    }

    if(state_player1Win && state_player2Win) {

        CSurface::OnDraw(Surf_Display, Surf_TieWin, 0, 100);
    }
    else if(state_player1Win) {

        CSurface::OnDraw(Surf_Display, Surf_Player1Win, 0, 100);
    }
    else if(state_player2Win) {

        CSurface::OnDraw(Surf_Display, Surf_Player2Win, 0, 100);
    }



    SDL_Flip(Surf_Display);

}

//------------------------------------------------------------------------------------------------------------------


void CApp::displaySelectElement(int stage) {

    std::string temp = "Pokemon ";
    temp.append(itoa(stage, buffer, 10));

    CSurface::OnDraw(Surf_Display, Surf_SelectElementScreen, 0, 0);
    Surf_TextHolder = TTF_RenderText_Blended( font30, temp.c_str(), textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 280, 550);
    SDL_FreeSurface(Surf_TextHolder);

    if(hoveredElement == findElement(locX, locY))
        hoveredElementTooltipTimer++;
    else {
        hoveredElement = findElement(locX, locY);
        hoveredElementTooltipTimer = 0;
    }
    if(hoveredElement > -1) {

        if(hoveredElementTooltipTimer > 600)
            displayHoveredElementTooltip(hoveredElement);

    }

}


void CApp::drawYourStats() {

    textColor = { 255, 255, 255 };
    Surf_TextHolder = TTF_RenderText_Blended( font18, currentBattle->player1->getActivePokemon()->nickname.c_str(), textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 399, 403);
    SDL_FreeSurface(Surf_TextHolder);

    Surf_TextHolder = TTF_RenderText_Blended( font18, "Stamina:", textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 399, 433);
    SDL_FreeSurface(Surf_TextHolder);

    int stamina = currentBattle->player1->getActivePokemon()->getStamina();
    Surf_TextHolder = TTF_RenderText_Blended( font18, itoa(stamina, buffer, 10), textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 484, 433);
    SDL_FreeSurface(Surf_TextHolder);

    if(currentBattle->player1->getActivePokemon()->getStatus() == 1) {
        CSurface::OnDraw(Surf_Display, Surf_PoisonSymbol, 628, 538);
    }
    if(currentBattle->player1->spikes) {
        CSurface::OnDraw(Surf_Display, Surf_SpikesSymbol, 555, 538);
    }
    if(currentBattle->player1->bomb) {
        CSurface::OnDraw(Surf_Display, Surf_BombSymbol, 482, 538);
    }

    if(currentBattle->player1->defenseBuff != 0) {

        if(currentBattle->player1->defenseBuff == 20)
            CSurface::OnDraw(Surf_Display, Surf_DefenseBuffSymbol, 400, 538, 0, 130-52, 60, 52);
        if(currentBattle->player1->defenseBuff == 30)
            CSurface::OnDraw(Surf_Display, Surf_DefenseBuffSymbol, 400, 538-26, 0, 130-78, 60, 78);
        if(currentBattle->player1->defenseBuff == 40)
            CSurface::OnDraw(Surf_Display, Surf_DefenseBuffSymbol, 400, 538-52, 0, 130-104, 60, 104);
        if(currentBattle->player1->defenseBuff == 45)
            CSurface::OnDraw(Surf_Display, Surf_DefenseBuffSymbol, 400, 538-65, 0, 130-117, 60, 117);
        if(currentBattle->player1->defenseBuff == 50)
            CSurface::OnDraw(Surf_Display, Surf_DefenseBuffSymbol, 400, 538-78, 0, 130-130, 60, 130);

    }

    textColor = { 0, 0, 0 };

}

void CApp::drawOpponentsStats() {

    textColor = { 255, 255, 255 };
    Surf_TextHolder = TTF_RenderText_Blended( font18, currentBattle->player2->getActivePokemon()->nickname.c_str(), textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 15, 10);
    SDL_FreeSurface(Surf_TextHolder);

    Surf_TextHolder = TTF_RenderText_Blended( font18, "Stamina:", textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 15, 40);
    SDL_FreeSurface(Surf_TextHolder);

    int stamina = currentBattle->player2->getActivePokemon()->getStamina();
    Surf_TextHolder = TTF_RenderText_Blended( font18, itoa(stamina, buffer, 10), textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 100, 40);
    SDL_FreeSurface(Surf_TextHolder);


    if(currentBattle->player2->getActivePokemon()->getStatus() == 1) {
        CSurface::OnDraw(Surf_Display, Surf_PoisonSymbol, 240, 98);
    }
    if(currentBattle->player2->spikes) {
        CSurface::OnDraw(Surf_Display, Surf_SpikesSymbol, 170, 98);
    }
    if(currentBattle->player2->bomb) {
        CSurface::OnDraw(Surf_Display, Surf_BombSymbol, 100, 98);
    }
    if(currentBattle->player2->defenseBuff != 0) {

        if(currentBattle->player2->defenseBuff == 20)
            CSurface::OnDraw(Surf_Display, Surf_DefenseBuffSymbol, 10, 98, 0, 130-52, 60, 52);
        if(currentBattle->player2->defenseBuff == 30)
            CSurface::OnDraw(Surf_Display, Surf_DefenseBuffSymbol, 10, 98-26, 0, 130-78, 60, 78);
        if(currentBattle->player2->defenseBuff == 40)
            CSurface::OnDraw(Surf_Display, Surf_DefenseBuffSymbol, 10, 98-52, 0, 130-104, 60, 104);
        if(currentBattle->player2->defenseBuff == 45)
            CSurface::OnDraw(Surf_Display, Surf_DefenseBuffSymbol, 10, 98-65, 0, 130-117, 60, 117);
        if(currentBattle->player2->defenseBuff == 50)
            CSurface::OnDraw(Surf_Display, Surf_DefenseBuffSymbol, 10, 98-78, 0, 130, 60, 130);

    }

    textColor = { 0, 0, 0 };

}

void CApp::drawMovesInButtons() {

    std::string elementLabel = "Element: ";
    std::string temp;

    Surf_TextHolder = TTF_RenderText_Blended( font18, currentBattle->player1->getActivePokemon()->getMove(0)->getName().c_str(), textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 60+30, 30+100);
    SDL_FreeSurface(Surf_TextHolder);
    temp = figureElementLabel(elementLabel, 0);
    Surf_TextHolder = TTF_RenderText_Blended( font18, temp.c_str(), textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 60+30, 30+100+20);
    SDL_FreeSurface(Surf_TextHolder);

    Surf_TextHolder = TTF_RenderText_Blended( font18, currentBattle->player1->getActivePokemon()->getMove(1)->getName().c_str(), textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 420+30, 30+100);
    SDL_FreeSurface(Surf_TextHolder);
    temp = figureElementLabel(elementLabel, 1);
    Surf_TextHolder = TTF_RenderText_Blended( font18, temp.c_str(), textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 420+30, 30+100+20);
    SDL_FreeSurface(Surf_TextHolder);

    Surf_TextHolder = TTF_RenderText_Blended( font18, currentBattle->player1->getActivePokemon()->getMove(2)->getName().c_str(), textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 60+30, 280+100);
    SDL_FreeSurface(Surf_TextHolder);
    temp = figureElementLabel(elementLabel, 2);
    Surf_TextHolder = TTF_RenderText_Blended( font18, temp.c_str(), textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 60+30, 280+100+20);
    SDL_FreeSurface(Surf_TextHolder);

    Surf_TextHolder = TTF_RenderText_Blended( font18, currentBattle->player1->getActivePokemon()->getMove(3)->getName().c_str(), textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 420+30, 280+100);
    SDL_FreeSurface(Surf_TextHolder);
    temp = figureElementLabel(elementLabel, 3);
    Surf_TextHolder = TTF_RenderText_Blended( font18, temp.c_str(), textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 420+30, 280+100+20);
    SDL_FreeSurface(Surf_TextHolder);

    textColor = { 0, 0, 0 };

}

void CApp::drawPokemonInSelections() {

    Pokemon* tempPoke;

    //tempPoke = currentBattle->player1->team.at(0);
    Surf_TextHolder = TTF_RenderText_Blended( font14, currentBattle->player1->team.at(0)->nickname.c_str(), textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 250+30, 30+100);
    SDL_FreeSurface(Surf_TextHolder);
    Surf_TextHolder = TTF_RenderText_Blended( font14, figurePokemonType(currentBattle->player1->team.at(0)->getElement()).c_str(), textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 250+30, 45+100);
    SDL_FreeSurface(Surf_TextHolder);

    Surf_TextHolder = TTF_RenderText_Blended( font14, currentBattle->player1->team.at(1)->nickname.c_str(), textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 80+30, 279+100);
    SDL_FreeSurface(Surf_TextHolder);
    Surf_TextHolder = TTF_RenderText_Blended( font14, figurePokemonType(currentBattle->player1->team.at(1)->getElement()).c_str(), textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 80+30, 294+100);
    SDL_FreeSurface(Surf_TextHolder);

    Surf_TextHolder = TTF_RenderText_Blended( font14, currentBattle->player1->team.at(2)->nickname.c_str(), textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 436+30, 279+100);
    SDL_FreeSurface(Surf_TextHolder);
    Surf_TextHolder = TTF_RenderText_Blended( font14, figurePokemonType(currentBattle->player1->team.at(2)->getElement()).c_str(), textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 436+30, 294+100);
    SDL_FreeSurface(Surf_TextHolder);

}

std::string CApp::figureElementLabel(std::string label, int moveNumber) {

    int tempElement = currentBattle->player1->getActivePokemon()->getMove(moveNumber)->getElement();
    if(tempElement == 0)
        label = label + "Martial";
    if(tempElement == 1)
        label = label + "Mental";
    if(tempElement == 2)
        label = label + "Spirit";
    if(tempElement == 3)
        label = label + "Fire";
    if(tempElement == 4)
        label = label + "Water";
    if(tempElement == 5)
        label = label + "Wood";
    if(tempElement == 6)
        label = label + "Electric";
    if(tempElement == 7)
        label = label + "Ground";
    if(tempElement == 8)
        label = label + "Metal";

    return label;

}

std::string CApp::figurePokemonType(int element) {

    std::string label;

    if(element == 0)
        label = "Martial";
    if(element == 1)
        label = "Mental";
    if(element == 2)
        label = "Spirit";
    if(element == 3)
        label = "Fire";
    if(element == 4)
        label = "Water";
    if(element == 5)
        label = "Wood";
    if(element == 6)
        label = "Electric";
    if(element == 7)
        label = "Ground";
    if(element == 8)
        label = "Metal";

    return label;

}


void CApp::displayHoveredElementTooltip(int hoveredElement) {


    textColor = { 255, 255, 255 };

    if(hoveredElement == 0) {

        Surf_TextHolder = TTF_RenderText_Blended( font24, "-Martial-", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 50, 200);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Mild Offensive", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 50, 200+34);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Uses tempo attacks to grind down the opponent", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 50, 200+68);
        SDL_FreeSurface(Surf_TextHolder);

    }
    if(hoveredElement == 1) {

        Surf_TextHolder = TTF_RenderText_Blended( font24, "-Mental-", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 350+200, 200);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Mild Support", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 350+180, 200+34);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Uses DOTs to grind down the opponent", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 300, 200+68);
        SDL_FreeSurface(Surf_TextHolder);

    }
    if(hoveredElement == 2) {

        Surf_TextHolder = TTF_RenderText_Blended( font24, "-Spirit-", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 100+210, 260);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Mild Defensive", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 100+180, 260+34);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Uses fake-outs and trickery to grind down the opponent", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 110, 260+68);
        SDL_FreeSurface(Surf_TextHolder);

    }
    if(hoveredElement == 3) {

        Surf_TextHolder = TTF_RenderText_Blended( font24, "-Fire-", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 50, 200);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Midi Offensive", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 50, 200+34);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Uses big bursts of damage to blow out the opponent", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 50, 200+68);
        SDL_FreeSurface(Surf_TextHolder);

    }
    if(hoveredElement == 4) {

        Surf_TextHolder = TTF_RenderText_Blended( font24, "-Water-", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 350+200, 200);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Midi Support", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 350+180, 200+34);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Uses healing and debuffs to outlast the opponent", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 200, 200+68);
        SDL_FreeSurface(Surf_TextHolder);

    }
    if(hoveredElement == 5) {

        Surf_TextHolder = TTF_RenderText_Blended( font24, "-Wood-", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 100+210, 260);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Midi Defensive", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 100+180, 260+34);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Uses buffs to outlast the opponent", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 200, 260+68);
        SDL_FreeSurface(Surf_TextHolder);

    }
    if(hoveredElement == 6) {

        Surf_TextHolder = TTF_RenderText_Blended( font24, "-Electric-", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 50, 200);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Extreme Offensive", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 50, 200+34);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Uses initiative to out-do the opponent", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 50, 200+68);
        SDL_FreeSurface(Surf_TextHolder);

    }
    if(hoveredElement == 7) {

        Surf_TextHolder = TTF_RenderText_Blended( font24, "-Ground-", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 350+200, 200);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Extreme Support", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 350+160, 200+34);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Uses traps to catch the opponent", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 380, 200+68);
        SDL_FreeSurface(Surf_TextHolder);

    }
    if(hoveredElement == 8) {

        Surf_TextHolder = TTF_RenderText_Blended( font24, "-Metal-", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 100+220, 260);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Extreme Defensive", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 100+180, 260+34);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Uses bulk to negate the opponent", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 210, 260+68);
        SDL_FreeSurface(Surf_TextHolder);

    }


    textColor = { 0, 0, 0 };

}

void CApp::displayBattle() {

    CSurface::OnDraw(Surf_Display, Surf_Background, 0, 0);
    CSurface::OnDraw(Surf_Display, Surf_Overlay, 0, 0);
    CSurface::OnDraw(Surf_Display, Surf_YourStats, 384, 393);
    drawYourStats();
    CSurface::OnDraw(Surf_Display, Surf_OpponentsStats, 0, 0);
    drawOpponentsStats();

    if(currentBattle->poke1Knockout == true) {
        if(currentBattle->hitTimerPoke1 == 0 && knockoutTimer1 == 0)
            knockoutTimer1 = 400;
            //knockoutTimer1 = currentBattle->hitTimerPoke1 + 400;

        //if(currentBattle->hitTimerPoke1 == 0) //Doesn't Work
            state_switchPokemon = true;
    }

    if(currentBattle->poke2Knockout == true && animateKnockoutBool) {
        if(currentBattle->hitTimerPoke2 == 0) {
            knockoutTimer2 = 400;
            animateKnockoutBool = false;
        }
        //knockoutTimer2 = currentBattle->hitTimerPoke2 + 400;
    }

    if(knockoutTimer1!=0) {
        Surf_TextHolder = TTF_RenderText_Shaded( font24, "Knockout!", {255, 255, 255}, {0, 0, 0} );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 130, 260);
        SDL_FreeSurface(Surf_TextHolder);
        knockoutTimer1--;
    }

    if(knockoutTimer2!=0) {
        Surf_TextHolder = TTF_RenderText_Shaded( font24, "Knockout!", {255, 255, 255}, {0, 0, 0} );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 450, 130);
        SDL_FreeSurface(Surf_TextHolder);
        knockoutTimer2--;
    }

    if(currentBattle->player1Attack || currentBattle->player2Attack) {

        if(!currentBattle->player1Attack) {
            animateBeingHitPoke1();
        }
        if(!currentBattle->player2Attack) {
            animateBeingHitPoke2();
        }
        if(currentBattle->poke2Move->getPriorityLevel() < currentBattle->poke1Move->getPriorityLevel()) {
            animateBeingHitPoke1();
            if(hitByTimerPoke1 == 0)
                animateBeingHitPoke2();
        }
        if(currentBattle->poke1Move->getPriorityLevel() < currentBattle->poke2Move->getPriorityLevel()) {
            animateBeingHitPoke2();
            if(hitByTimerPoke2 == 0)
                animateBeingHitPoke1();
        }
        else {
            animateBeingHitPoke1();
            animateBeingHitPoke2();
        }

    }
    else {
        animateBeingHitPoke1();
        animateBeingHitPoke2();
    }

    if(state_switchPokemon) {

        //if(currentBattle->hitTimerPoke1 == 0 && knockoutTimer1 == 0) {
        if(!((currentBattle->player2TeamCount == 0 || currentBattle->player1TeamCount == 0) && !state_welcomeScreen)) {

            CSurface::OnDraw(Surf_Display, Surf_SwitchPokemonOverlay, 30, 100);
            drawPokemonInSelections();

        }
        //}

    }
    else if(state_moveOverlay) {

        CSurface::OnDraw(Surf_Display, Surf_MoveOverlay, 30, 100);
        drawMovesInButtons();

    }

}

void CApp::animateBeingHitPoke1() {

    //Size of pokemon in sheet is 220 x 209
    if(currentBattle->hitTimerPoke1 == 0 || (currentBattle->hitTimerPoke1 >= 150 && currentBattle->hitTimerPoke1 <= 250)) {
        CSurface::OnDraw(Surf_Display, Surf_PokemonSheet, 75, 280, 220*(currentBattle->player1->getActivePokemon()->getElement()), 0, 220, 209);
        //Draw dots
        CSurface::OnDraw(Surf_Display, Surf_DotSheet, 75-3, 280-3, 13*(currentBattle->player1->getActivePokemon()->pokeMoveSet.at(0)->getElement()), 0, 13, 13);
        CSurface::OnDraw(Surf_Display, Surf_DotSheet, 75+3+220, 280-3, 13*(currentBattle->player1->getActivePokemon()->pokeMoveSet.at(1)->getElement()), 0, 13, 13);
        CSurface::OnDraw(Surf_Display, Surf_DotSheet, 75-3, 280+3+209, 13*(currentBattle->player1->getActivePokemon()->pokeMoveSet.at(2)->getElement()), 0, 13, 13);
        CSurface::OnDraw(Surf_Display, Surf_DotSheet, 75+3+220, 280+3+209, 13*(currentBattle->player1->getActivePokemon()->pokeMoveSet.at(3)->getElement()), 0, 13, 13);
        //Draw squares
        for(int i=0; i<9; i++) {
            if(currentBattle->player1->getActivePokemon()->elementChangeTracker.at(i) == 1)
                CSurface::OnDraw(Surf_Display, Surf_ChangeSquaresSheet, 420+(25*i), 473, 20*(i), 0, 20, 20);
        }

        if(currentBattle->hitTimerPoke1 >= 150 && currentBattle->hitTimerPoke1 <= 250) {
            currentBattle->hitTimerPoke1--;
        }
    }
    else {
        currentBattle->hitTimerPoke1--;
    }

    if(hitByTimerPoke1) {
        //If hit by opposing pokemon
        if(currentBattle->player2Attack) {
            //If poke2 attacks, display what hit poke1
            Surf_TextHolder = TTF_RenderText_Shaded( font18, ("Hit by " + currentBattle->poke2Move->getName()).c_str(), {255, 255, 255}, {0, 0, 0} );
            CSurface::OnDraw(Surf_Display, Surf_TextHolder, 130 + hitByMessagePoke1.CurrentFrame/6, 260);
            SDL_FreeSurface(Surf_TextHolder);
            hitByMessagePoke1.CurrentFrame++;

            //Should have its own function
            if(currentBattle->player1->getActivePokemon()->getStatus() == 1) {
                Surf_TextHolder = TTF_RenderText_Blended( font18, "Poison Damage...", textColor );
                CSurface::OnDraw(Surf_Display, Surf_TextHolder, 564, 433);
                SDL_FreeSurface(Surf_TextHolder);
            }
        }
        hitByTimerPoke1--;
    }

}

void CApp::animateBeingHitPoke2() {

    //Size of pokemon in sheet is 220 x 209
    if(currentBattle->hitTimerPoke2 == 0|| (currentBattle->hitTimerPoke2 >= 150 && currentBattle->hitTimerPoke2 <= 250)) {
        CSurface::OnDraw(Surf_Display, Surf_PokemonSheet, 400, 150, 220*(currentBattle->player2->getActivePokemon()->getElement()), 0, 220, 209);
        //Draw dots
        CSurface::OnDraw(Surf_Display, Surf_DotSheet, 400-3, 150-3, 13*(currentBattle->player2->getActivePokemon()->pokeMoveSet.at(0)->getElement()), 0, 13, 13);
        CSurface::OnDraw(Surf_Display, Surf_DotSheet, 400+3+220, 150-3, 13*(currentBattle->player2->getActivePokemon()->pokeMoveSet.at(1)->getElement()), 0, 13, 13);
        CSurface::OnDraw(Surf_Display, Surf_DotSheet, 400-3, 150+3+209, 13*(currentBattle->player2->getActivePokemon()->pokeMoveSet.at(2)->getElement()), 0, 13, 13);
        CSurface::OnDraw(Surf_Display, Surf_DotSheet, 400+3+220, 150+3+209, 13*(currentBattle->player2->getActivePokemon()->pokeMoveSet.at(3)->getElement()), 0, 13, 13);

        if(currentBattle->hitTimerPoke2 >= 150 && currentBattle->hitTimerPoke2 <= 250) {
            currentBattle->hitTimerPoke2--;
        }
    }
    else {
        currentBattle->hitTimerPoke2--;
    }

    if(hitByTimerPoke2) {
        //If hit by opposing pokemon
        if(currentBattle->player1Attack) {
            //If poke1 attacks, display what hit poke2
            Surf_TextHolder = TTF_RenderText_Shaded( font18, ("Hit by " + currentBattle->poke1Move->getName()).c_str(), {255, 255, 255}, {0, 0, 0} );
            CSurface::OnDraw(Surf_Display, Surf_TextHolder, 450 - hitByMessagePoke2.CurrentFrame/6, 130);
            SDL_FreeSurface(Surf_TextHolder);
            hitByMessagePoke2.CurrentFrame++;

            //Should have its own function
            if(currentBattle->player2->getActivePokemon()->getStatus() == 1) {
                Surf_TextHolder = TTF_RenderText_Blended( font18, "Poison Damage...", textColor );
                CSurface::OnDraw(Surf_Display, Surf_TextHolder, 180, 40);
                SDL_FreeSurface(Surf_TextHolder);
            }
        }
        hitByTimerPoke2--;
    }

}

void CApp::drawMovesInSelections(int element) {

    if(element == 0) {
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Bounce Back", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 110);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 70%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 140);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Play Cool", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 110);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 60%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 140);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Beatdown", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 360);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 100%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 390);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Strike", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 360);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 100%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 390);
        SDL_FreeSurface(Surf_TextHolder);
    }
    if(element == 1) {
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Corrupt", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 110);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 30%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 140);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Will Away", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 110);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 60%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 140);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Taunt", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 360);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 50%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 390);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Focus", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 360);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 100%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 390);
        SDL_FreeSurface(Surf_TextHolder);
    }
    if(element == 2) {
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Fake Out", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 110);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 60%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 140);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Enfeeble", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 110);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 60%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 140);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Blink", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 360);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 120%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 390);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Baffle", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 360);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 100%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 390);
        SDL_FreeSurface(Surf_TextHolder);
    }
    if(element == 3) {
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Power Flare", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 110);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 150%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 140);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Blaze Off", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 110);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 60%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 140);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Power Bomb", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 360);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 170%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 390);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Blast", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 360);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 100%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 390);
        SDL_FreeSurface(Surf_TextHolder);
    }
    if(element == 4) {
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Soothe", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 110);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 0%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 140);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Stave Off", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 110);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 60%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 140);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Correct", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 360);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 30%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 390);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Pump", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 360);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 100%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 390);
        SDL_FreeSurface(Surf_TextHolder);
    }
    if(element == 5) {
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Bastion", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 110);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 30%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 140);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Ward Off", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 110);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 60%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 140);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Topple", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 360);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 100%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 390);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Smack", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 360);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 100%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 390);
        SDL_FreeSurface(Surf_TextHolder);
    }
    if(element == 6) {
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Light Speed", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 110);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 80%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 140);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Piercing Volt", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 110);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 100%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 140);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Reroute", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 360);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 100%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 390);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Charge", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 360);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 100%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 390);
        SDL_FreeSurface(Surf_TextHolder);
    }
    if(element == 7) {
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Spikes", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 110);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 30%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 140);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Preparation", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 110);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 100%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 140);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Parry", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 360);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 0%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 390);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Shake", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 360);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 100%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 390);
        SDL_FreeSurface(Surf_TextHolder);
    }
    if(element == 8) {
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Barter", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 110);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 50%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 140);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Haymaker", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 110);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 100%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 140);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Junk", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 360);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 130%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 160, 390);
        SDL_FreeSurface(Surf_TextHolder);

        Surf_TextHolder = TTF_RenderText_Blended( font24, "Smash", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 360);
        SDL_FreeSurface(Surf_TextHolder);
        Surf_TextHolder = TTF_RenderText_Blended( font24, "Damage: 100%", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 390);
        SDL_FreeSurface(Surf_TextHolder);
    }


}

void CApp::displaySelectMoves(int poke) {

    CSurface::OnDraw(Surf_Display, Surf_MoveSelectTemplate, 0, 0);

    if(state_selectTheMove > -1) {

        CSurface::OnDraw(Surf_Display, Surf_MoveSelectBlocksTemplate, 150, 70, 225*state_selectTheMove, 0, 225, 225);
        drawMovesInSelections(state_selectTheMove);
        CSurface::OnDraw(Surf_Display, Surf_MoveSelectBlocksTemplate, 420, 70, 225*state_selectTheMove, 0, 225, 225);
        drawMovesInSelections(state_selectTheMove);
        CSurface::OnDraw(Surf_Display, Surf_MoveSelectBlocksTemplate, 150, 320, 225*state_selectTheMove, 0, 225, 225);
        drawMovesInSelections(state_selectTheMove);
        CSurface::OnDraw(Surf_Display, Surf_MoveSelectBlocksTemplate, 420, 320, 225*state_selectTheMove, 0, 225, 225);
        drawMovesInSelections(state_selectTheMove);

    }

    if(poke == 0) {
        Surf_TextHolder = TTF_RenderText_Blended( font36, "Pokemon 1", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 280, 550);
        SDL_FreeSurface(Surf_TextHolder);
    }
    if(poke == 1) {
        Surf_TextHolder = TTF_RenderText_Blended( font36, "Pokemon 2", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 280, 550);
        SDL_FreeSurface(Surf_TextHolder);
    }
    if(poke == 2) {
        Surf_TextHolder = TTF_RenderText_Blended( font36, "Pokemon 3", textColor );
        CSurface::OnDraw(Surf_Display, Surf_TextHolder, 280, 550);
        SDL_FreeSurface(Surf_TextHolder);
    }

    Surf_TextHolder = TTF_RenderText_Blended( font48, "Select Moves", textColor );
    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 260, 20);
    SDL_FreeSurface(Surf_TextHolder);

}

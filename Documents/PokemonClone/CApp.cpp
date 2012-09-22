#include "CApp.h"

CApp::CApp() {

    Surf_Background = NULL;
    Surf_DialogBackground = NULL;
    Surf_DialogBackgroundBox = NULL;
    Surf_Overlay = NULL;
    Surf_Display = NULL;
    Surf_MoveOverlay = NULL;
    Surf_SwitchPokemonOverlay = NULL;
    Surf_SelectElementScreen = NULL;
    Surf_WelcomeScreen = NULL;
    Surf_HelpScreen = NULL;
    Surf_MoveSelectTemplate = NULL;
    Surf_MoveSelectBlocksTemplate = NULL;
    Surf_PokemonSheet = NULL;
    Surf_DotSheet = NULL;
    Surf_ChangeSquaresSheet = NULL;
    Surf_YourStats = NULL;
    Surf_OpponentsStats = NULL;
    Surf_PoisonSymbol = NULL;
    Surf_SpikesSymbol = NULL;
    Surf_BombSymbol = NULL;
    Surf_DefenseBuffSymbol = NULL;
    Surf_TextHolder = NULL;
    Surf_Player1Win = NULL;
    Surf_Player2Win = NULL;
    Surf_TieWin = NULL;

    font14 = NULL;
    font18 = NULL;
    font24 = NULL;
    font30 = NULL;
    font36 = NULL;



    Running = true;

    state_welcomeScreen = true;
    state_helpScreen = false;
    state_storyScreen = false;
    state_selectElement1 = false;
    state_selectElement2 = false;
    state_selectElement3 = false;
    state_selectMoves1 = false;
    state_selectMoves2 = false;
    state_selectMoves3 = false;
    state_elementSelected = false;
    state_selectTheMove = -1;
    state_moveOverlay = false;
    state_switchPokemon = false;
    state_player1Win = false;
    state_player2Win = false;

    hoveredElementTooltipTimer = 0;

    winMessageDelay = 400;

    delayTimer = 0;
    knockoutTimer1 = 0;
    knockoutTimer2 = 0;
    hitByTimerPoke1 = 0;
    hitByTimerPoke2 = 0;
    winTimer = -1;
    //hitByAnimationTicksPoke1 = 0;
    //hitByAnimationTicksPoke2 = 0;

    battleStage = 1;

    player1Ready = false;
    player2Ready = false;
    setBattleOff = false;
    waitingForKnockoutSwitch = false;
    animateKnockoutBool = false;

    bounceBackSwitch = false;


    player1 = new Player();

    player2 = new Player();

    currentBattle = new Battle(player1, player2);

}

int CApp::OnExecute() {
    if(OnInit() == false) {
        return -1;
    }

    SDL_Event Event;

    while(Running) {

        if(delayTimer == 0) {
            while(SDL_PollEvent(&Event)) {
                OnEvent(&Event);
            }
        }
        if(delayTimer == 0) {
            OnLoop();
        }
        if(delayTimer == 0) {
            OnRender();
        }
        if(delayTimer != 0)
            delayTimer--;

    }

    OnCleanup();

    return 0;
}



int main(int argc, char* argv[]) {
    CApp theApp;

    srand ( time(NULL) );

    return theApp.OnExecute();
}

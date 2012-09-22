#include "CApp.h"

bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if((Surf_Display = SDL_SetVideoMode(700, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }

    if(TTF_Init() == -1)
    {
        return false;
    }

    if(!loadSurfaces()) {
        return false;
    }


    textColor = { 0, 0, 0 };


    //player1 = new Player();
    //player2 = new Player();


    font14 = TTF_OpenFont( "Sommet.ttf", 14 );
    font18 = TTF_OpenFont( "Sommet.ttf", 18 );
    font24 = TTF_OpenFont( "Sommet.ttf", 24 );
    font30 = TTF_OpenFont( "Sommet.ttf", 30 );
    font36 = TTF_OpenFont( "Sommet.ttf", 36 );
    font48 = TTF_OpenFont( "Sommet.ttf", 48 );

    if( font14 == NULL )
        return false;

    if( !fetchMoveData() )
        return false;

    hitByMessagePoke1.MaxFrames = 1000;
    hitByMessagePoke2.MaxFrames = 1000;



    //CSurface::Transparent(Surf_Overlay, 255, 255, 255);



    return true;
}

//----------------------------------------------------------------------------------------------------

bool CApp::loadSurfaces() {

    if((CApp::Surf_Background = CSurface::OnLoad("images/mountainBackground.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_DialogBackground = CSurface::OnLoad("images/dialogBackground.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_DialogBackgroundBox = CSurface::OnLoad("images/dialogBackgroundBox.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_Overlay = CSurface::OnLoad("images/overlay.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_MoveOverlay = CSurface::OnLoad("images/moveOverlayMark2.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_SelectElementScreen = CSurface::OnLoad("images/selectElementScreen.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_SwitchPokemonOverlay = CSurface::OnLoad("images/switchPokemonOverlay.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_WelcomeScreen = CSurface::OnLoad("images/welcomeScreen.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_HelpScreen = CSurface::OnLoad("images/helpScreen.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_MoveSelectTemplate = CSurface::OnLoad("images/moveSelectTemplate.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_MoveSelectBlocksTemplate = CSurface::OnLoad("images/moveSelectBlocksTemplate.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_PokemonSheet = CSurface::OnLoad("images/pokemonSheet.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_DotSheet = CSurface::OnLoad("images/dotSheet.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_ChangeSquaresSheet = CSurface::OnLoad("images/changeSquaresSheet.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_YourStats = CSurface::OnLoad("images/yourStats.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_OpponentsStats = CSurface::OnLoad("images/opponentsStats.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_PoisonSymbol = CSurface::OnLoad("images/poisonSymbol.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_SpikesSymbol = CSurface::OnLoad("images/spikesSymbol.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_BombSymbol = CSurface::OnLoad("images/bombSymbol.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_DefenseBuffSymbol = CSurface::OnLoad("images/defenseBuffSymbol.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_TextHolder = CSurface::OnLoad("images/opponentsStats.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_Player1Win = CSurface::OnLoad("images/winMessagePlayer1.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_Player2Win = CSurface::OnLoad("images/winMessagePlayer2.png")) == NULL) {
        return false;
    }

    if((CApp::Surf_TieWin = CSurface::OnLoad("images/winMessageTie.png")) == NULL) {
        return false;
    }

    return true;

}

bool CApp::fetchMoveData() { //Needs to implement checking

    FILE* moveFile = fopen("moveData.txt", "r");
    int tempID, tempSpec, tempMult, tempPower, tempElement, tempPriority;
    bool tempSpecial, tempMulti;
    int totalMoves = 36;

    for(int i=0; i < totalMoves; i++) {

        fscanf(moveFile, "%d:%d:%d:%d:%d:%d", &tempID, &tempSpec, &tempMult, &tempPower, &tempElement, &tempPriority);
        tempSpecial = (bool) tempSpec; tempMulti = (bool) tempMult;
        Move* temp = new Move(tempID, tempSpecial, tempMulti, tempPower, tempElement, tempPriority);
        Move::moveDataSet.push_back(temp);

    }

    fclose(moveFile);

    //------------------------------------------------------------------

    FILE* nameFile = fopen("moveNames.txt", "r");

    std::string tempStr;

    for(int k=0; k < totalMoves; k++) {

        char tempCStr [80];
        fscanf(nameFile, "%s", tempCStr);
        for(int j=0; j < tempStr.size(); j++) {
            //Doesnt work
            if(tempStr.at(j) == '_')
                tempStr.replace(j,1,1,' ');
        }
        tempStr = tempCStr;
        Move::moveNames.push_back(tempStr);
        delete [] tempCStr;

    }

    fclose(nameFile);



    return true;

}

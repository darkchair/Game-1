#include "CApp.h"

CApp::CApp() {
    Surf_Background = NULL;
    Surf_ShipPanel = NULL;
    Surf_Ship = NULL;
    Surf_InfoVisor = NULL;
    Surf_InterceptorPanel = NULL;
    Surf_HackingPanel = NULL;
        Surf_SteamIcon = NULL;
        Surf_ElectricalIcon = NULL;
    Surf_DialogBackground = NULL;
    Surf_DialogBox = NULL;
    Surf_EnemyShip = NULL;
    Surf_TextHolder = NULL;

    Surf_Display = NULL;

    Sommet18 = NULL;
    Sommet24 = NULL;
    Sommet30 = NULL;
    textColor = {255, 255, 255};


    state_infoVisorUp = false;
    state_interceptorBattle = false;
    state_hackingBattle = false;
    state_dialog = false;



    Running = true;
}

int CApp::OnExecute() {
    if(OnInit() == false) {
        return -1;
    }

    SDL_Event Event;

    while(Running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}

int main(int argc, char* argv[]) {
    CApp theApp;

    srand ( time(NULL) );

    return theApp.OnExecute();
}

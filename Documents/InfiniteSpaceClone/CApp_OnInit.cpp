#include "CApp.h"

bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if (TTF_Init() < 0) {
        return false;
    }

    if((Surf_Display = SDL_SetVideoMode(1000, 700, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }

    if((Surf_Background = CSurface::OnLoad("Images/background.png")) == NULL) {
        return false;
    }
    if((Surf_ShipPanel = CSurface::OnLoad("Images/shipPanelTemplate.png")) == NULL) {
        return false;
    }
        ShipPanelAnimation.MaxFrames = 500;

    if((Surf_Ship = CSurface::OnLoad("Images/ship1Template.png")) == NULL) {
        return false;
    }
    if((Surf_InfoVisor = CSurface::OnLoad("Images/infoVisorTemplate.png")) == NULL) {
        return false;
    }
    if((Surf_InterceptorPanel = CSurface::OnLoad("Images/interceptorTemplate.png")) == NULL) {
        return false;
    }
    if((Surf_DialogBackground = CSurface::OnLoad("Images/dialogBackground.png")) == NULL) {
        return false;
    }
    if((Surf_DialogBox = CSurface::OnLoad("Images/dialogBox.png")) == NULL) {
        return false;
    }
    if((Surf_EnemyShip = CSurface::OnLoad("Images/enemyShip1Template.png")) == NULL) {
        return false;
    }
    if((Surf_TextHolder = CSurface::OnLoad("Images/opponentsStats.png")) == NULL) {
        return false;
    }
    if((Surf_HackingPanel = CSurface::OnLoad("Images/hackingTemplate.png")) == NULL) {
        return false;
    }
    if((Surf_SteamIcon = CSurface::OnLoad("Images/steamIcon.png")) == NULL) {
        return false;
    }
    if((Surf_ElectricalIcon = CSurface::OnLoad("Images/electricalIcon.png")) == NULL) {
        return false;
    }

    Sommet18 = TTF_OpenFont("Sommet.ttf", 18);
    Sommet24 = TTF_OpenFont("Sommet.ttf", 24);
    Sommet30 = TTF_OpenFont("Sommet.ttf", 30);

    int random = rand() % 5 + 1;
    for(int i=0; i<random; i++)
        EnemyInterceptor::interceptors.push_back(new EnemyInterceptor());


    return true;
}

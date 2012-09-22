#include "CApp.h"

void CApp::OnCleanup() {

    SDL_FreeSurface(Surf_Background);
    SDL_FreeSurface(Surf_Overlay);
    SDL_FreeSurface(Surf_Display);
    TTF_Quit();
    SDL_Quit();

}

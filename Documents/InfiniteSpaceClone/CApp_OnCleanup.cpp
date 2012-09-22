#include "CApp.h"

void CApp::OnCleanup() {
    SDL_FreeSurface(Surf_Background);
    SDL_FreeSurface(Surf_Display);

    TTF_CloseFont(Sommet18);
    TTF_Quit();

    SDL_Quit();
}

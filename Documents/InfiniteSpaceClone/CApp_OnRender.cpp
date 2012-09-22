#include "CApp.h"

void CApp::OnRender() {
    if(state_dialog) {
        CSurface::OnDraw(Surf_Display, Surf_DialogBackground, 0, 0);
        CSurface::OnDraw(Surf_Display, Surf_DialogBox, 0, 420);
    }
    else {
        CSurface::OnDraw(Surf_Display, Surf_Background, 0, 0);

        if(state_interceptorBattle) {
            Coordinate temp = EnemyInterceptor::getPosition(0);
            CSurface::OnDraw(Surf_Display, Surf_EnemyShip, temp.x - 100, temp.y - 90);
            CSurface::OnDraw(Surf_Display, Surf_InterceptorPanel, 0, 0);

            if(EnemyInterceptor::shipHit) {
                if(EnemyInterceptor::interceptors.at(0)->hitTimer != 0) {
                    Surf_TextHolder = TTF_RenderText_Blended( Sommet18, "Hit Confirmed", textColor );
                    CSurface::OnDraw(Surf_Display, Surf_TextHolder, 430, 600);
                    SDL_FreeSurface(Surf_TextHolder);
                    EnemyInterceptor::interceptors.at(0)->hitTimer--;
                }
            }
        }
        else if(state_hackingBattle) {

            textColor = {119, 158, 117};

            CSurface::OnDraw(Surf_Display, Surf_HackingPanel, 0, 0);
            Surf_TextHolder = TTF_RenderText_Blended( Sommet30, "Command", textColor );
            CSurface::OnDraw(Surf_Display, Surf_TextHolder, 40, 40);
            SDL_FreeSurface(Surf_TextHolder);
            Surf_TextHolder = TTF_RenderText_Blended( Sommet30, "Help", textColor );
            CSurface::OnDraw(Surf_Display, Surf_TextHolder, 40, 80);
            SDL_FreeSurface(Surf_TextHolder);

            textColor = {255, 255, 255};

            CSurface::OnDraw(Surf_Display, Surf_SteamIcon, 420, 420);
            CSurface::OnDraw(Surf_Display, Surf_ElectricalIcon, 550, 420);

        }
        else {
            CSurface::OnDraw(Surf_Display, Surf_ShipPanel, 0, 0);
            CSurface::OnDraw(Surf_Display, Surf_Ship, 75, 140);
        }
    }
    if(state_infoVisorUp) {
        CSurface::OnDraw(Surf_Display, Surf_InfoVisor, 1000 - ShipPanelAnimation.CurrentFrame, 0);
        if(ShipPanelAnimation.CurrentFrame < 500)
            ShipPanelAnimation.CurrentFrame += 4;
        else {
            Surf_TextHolder = TTF_RenderText_Blended( Sommet18, "Dialog", textColor );
            CSurface::OnDraw(Surf_Display, Surf_TextHolder, 1070 - ShipPanelAnimation.CurrentFrame, 360);
            SDL_FreeSurface(Surf_TextHolder);
            Surf_TextHolder = TTF_RenderText_Blended( Sommet18, "Home", textColor );
            CSurface::OnDraw(Surf_Display, Surf_TextHolder, 1070 - ShipPanelAnimation.CurrentFrame, 460);
            SDL_FreeSurface(Surf_TextHolder);
            Surf_TextHolder = TTF_RenderText_Blended( Sommet18, "Engineering", textColor );
            CSurface::OnDraw(Surf_Display, Surf_TextHolder, 1220 - ShipPanelAnimation.CurrentFrame, 460);
            SDL_FreeSurface(Surf_TextHolder);
            Surf_TextHolder = TTF_RenderText_Blended( Sommet18, "Interceptors", textColor );
            CSurface::OnDraw(Surf_Display, Surf_TextHolder, 1370 - ShipPanelAnimation.CurrentFrame, 460);
            SDL_FreeSurface(Surf_TextHolder);
        }
    }
    else {
        if(ShipPanelAnimation.CurrentFrame > 0) {
            CSurface::OnDraw(Surf_Display, Surf_InfoVisor, 1000 - ShipPanelAnimation.CurrentFrame, 0);
            ShipPanelAnimation.CurrentFrame -= 4;
        }
    }

    SDL_Flip(Surf_Display);
}

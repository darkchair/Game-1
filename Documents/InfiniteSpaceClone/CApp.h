#ifndef CAPP_H_INCLUDED
#define CAPP_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include <time.h>

#include "CEvent.h"
#include "CSurface.h"
#include "CAnimation.h"

#include "EnemyInterceptor.h"

class CApp : public CEvent {
    private:
        bool            Running;

        SDL_Surface*    Surf_Display;

    private:
        SDL_Surface*    Surf_Background;
        SDL_Surface*    Surf_ShipPanel;
            CAnimation      ShipPanelAnimation;
        SDL_Surface*    Surf_Ship;
        SDL_Surface*    Surf_InfoVisor;
        SDL_Surface*    Surf_InterceptorPanel;
        SDL_Surface*    Surf_HackingPanel;
            SDL_Surface*    Surf_SteamIcon;
            SDL_Surface*    Surf_ElectricalIcon;
        SDL_Surface*    Surf_DialogBackground;
        SDL_Surface*    Surf_DialogBox;
        SDL_Surface*    Surf_EnemyShip;
        SDL_Surface*    Surf_TextHolder;

        TTF_Font*       Sommet18;
        TTF_Font*       Sommet24;
        TTF_Font*       Sommet30;

        SDL_Color       textColor;

    public:
        bool            state_infoVisorUp;
        bool            state_interceptorBattle;
        bool            state_hackingBattle;
        bool            state_dialog;


    public:
        CApp();

        int OnExecute();

    public:
        bool OnInit();

        void OnEvent(SDL_Event* Event);

            void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
            void OnLButtonDown(int mX, int mY);

        void OnExit();

        void OnLoop();

        void OnRender();

        void OnCleanup();

    public:


};

#endif // CAPP_H_INCLUDED

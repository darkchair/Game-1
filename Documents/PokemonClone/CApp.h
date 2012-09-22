#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL/SDL_ttf.h>

#include <iostream>
#include <sstream>
#include <stdio.h>

#include "CEvent.h"
#include "CSurface.h"
#include "CAnimation.h"

#include "Battle.h"


class CApp : public CEvent {


    private:

        bool            Running;

        bool            state_welcomeScreen;
        bool            state_helpScreen;

        bool            state_storyScreen;

        bool            state_selectElement1;
        bool            state_selectElement2;
        bool            state_selectElement3;

        bool            state_selectMoves1;
        bool            state_selectMoves2;
        bool            state_selectMoves3;
        bool            state_elementSelected;
        int             state_selectTheMove;
            int             chosenMoveElement;
            int             chosenMove;

        bool            state_moveOverlay;

        bool            state_switchPokemon;

        bool            state_player1Win;
        bool            state_player2Win;


        SDL_Surface*    Surf_Display;

    //Surfaces
    private:


        int locX;
        int locY;


        SDL_Surface*    Surf_Background;
        SDL_Surface*    Surf_DialogBackground;
        SDL_Surface*    Surf_DialogBackgroundBox;
        SDL_Surface*    Surf_Overlay;
        SDL_Surface*    Surf_MoveOverlay;
        SDL_Surface*    Surf_SwitchPokemonOverlay;
        SDL_Surface*    Surf_SelectElementScreen;
        SDL_Surface*    Surf_WelcomeScreen;
        SDL_Surface*    Surf_HelpScreen;
        SDL_Surface*    Surf_MoveSelectTemplate;
        SDL_Surface*    Surf_MoveSelectBlocksTemplate;
        SDL_Surface*    Surf_PokemonSheet;
        SDL_Surface*    Surf_DotSheet;
        SDL_Surface*    Surf_ChangeSquaresSheet;
        SDL_Surface*    Surf_YourStats;
        SDL_Surface*    Surf_OpponentsStats;
        SDL_Surface*    Surf_PoisonSymbol;
        SDL_Surface*    Surf_SpikesSymbol;
        SDL_Surface*    Surf_BombSymbol;
        SDL_Surface*    Surf_DefenseBuffSymbol;
        SDL_Surface*    Surf_TextHolder;
        SDL_Surface*    Surf_Player1Win;
        SDL_Surface*    Surf_Player2Win;
        SDL_Surface*    Surf_TieWin;


        TTF_Font*       font14;
        TTF_Font*       font18;
        TTF_Font*       font24;
        TTF_Font*       font30;
        TTF_Font*       font36;
        TTF_Font*       font48;

        SDL_Color       textColor;

        CAnimation      hitByMessagePoke1;
        CAnimation      hitByMessagePoke2;

        //For using itoa()
        char buffer [33];


        int battleStage;

        bool player1Ready;
        bool player2Ready;

        bool setBattleOff;
        bool waitingForKnockoutSwitch;

        //Move Logic
        bool bounceBackSwitch;

        //C_App_OnEvent()
        int hoveredElement;
        int hoveredElementTooltipTimer;

        int winMessageDelay;


        int delayTimer;
        int knockoutTimer1;
        int knockoutTimer2;
        int hitByTimerPoke1;
        int hitByTimerPoke2;
        int winTimer;
        //int hitByAnimationTicksPoke1;
        //int hitByAnimationTicksPoke2;

        CAnimation* animPoke1;
        CAnimation* animPoke2;

        bool animateKnockoutBool;




    private:

        Player* player1;

        Player* player2;


        Battle* currentBattle;


    public:

        CApp();

        int OnExecute();


    //Main Loop Functions
    public:

        bool OnInit();

        void OnEvent(SDL_Event* Event);

            void OnExit();

        void OnLoop();

        void OnRender();

        void OnCleanup();


    public:
        //Init Methods
        bool fetchMoveData();

        //Event Methods
        void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);

        void OnLButtonDown(int mX, int mY);

        bool atInitiateLocation(int mX, int mY);

        bool loadSurfaces();

        int findElement(int mX, int mY);

        int findMoveElement(int mX, int mY);

        int findMove(int mX, int mY, int chosenMoveElement);

        void addPokemon(int chosenElement, std::string name);

        bool addMove(int chosenMove, int poke);

        void welcomeScreenLogic(int mX, int mY);

        void switchPokemonLogic(int mX, int mY);

        void moveOverlayLogic(int mX, int mY);

        //Render Methods

        void displaySelectElement(int stage);

        void drawYourStats();

        void drawOpponentsStats();

        void drawMovesInButtons();

        void drawPokemonInSelections();

        std::string figureElementLabel(std::string label, int moveNumber);

        std::string figurePokemonType(int element);

        void displayHoveredElementTooltip(int hoveredElement);

        void displayBattle();

        void animateBeingHitPoke1();

        void animateBeingHitPoke2();

        void drawMovesInSelections(int element);

        void displaySelectMoves(int poke);


    public:


};

#endif

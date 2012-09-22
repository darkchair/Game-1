#include "CApp.h"

void CApp::OnEvent(SDL_Event* Event) {
    CEvent::OnEvent(Event);
}

void CApp::OnExit() {
    Running = false;
}

void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {

    if(sym == SDLK_SPACE) {
        if(state_infoVisorUp)
            state_infoVisorUp = false;
        else
            state_infoVisorUp = true;
    }

}

void CApp::OnLButtonDown(int mX, int mY) {

    if(state_infoVisorUp) {

        if(mX >= 560+306 && mY >= 160 && mX <= 1000 && mY <= 492) {
            state_interceptorBattle = true;
            state_hackingBattle = false;
            state_dialog = false;
        }
        else if(mX >= 560 && mY >= 392 && mX <= 560+140 && mY <= 492) {
            //if(state_interceptorBattle) {
                EnemyInterceptor::exitBattle();
                state_interceptorBattle = false;
            //}
            if(state_hackingBattle)
                state_hackingBattle = false;
            else if(state_dialog)
                state_dialog = false;
        }
        else if(mX >= 560+145 && mY >= 160 && mX <= 560+301 && mY <= 492) {
            state_dialog = false;
            state_interceptorBattle = false;
            state_hackingBattle = true;
        }
        else if(mX >= 560 && mY >= 160 && mX <= 560+140 && mY <= 390) {
            state_interceptorBattle = false;
            state_hackingBattle = false;
            state_dialog = true;
        }

    }

    else if(state_interceptorBattle) {

        for(int i=0; i<EnemyInterceptor::interceptors.size(); i++) {

            if(mX >= EnemyInterceptor::interceptors.at(i)->position.x - 100 && mY >= EnemyInterceptor::interceptors.at(i)->position.x - 90 &&
               mX <= EnemyInterceptor::interceptors.at(i)->position.x + 100 && mY <= EnemyInterceptor::interceptors.at(i)->position.x + 90) {
                //Damage the ship   damageShip(i)
                EnemyInterceptor::shipHit = true;
                EnemyInterceptor::interceptors.at(i)->damage++;
                if(EnemyInterceptor::interceptors.at(i)->hitTimer == 0)
                    EnemyInterceptor::interceptors.at(i)->hitTimer = 100;
            }


        }


    }

    else if(state_hackingBattle) {

        if(mX >= 0 && mY >= 0 && mX <= 205 && mY <= 246) {
            //Show Commands
        }

    }

}

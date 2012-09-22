#include "CAnimation.h"

CAnimation::CAnimation() {
    CurrentFrame    = 0;
    MaxFrames       = 0;
    hitFrames       = 0;
    FrameInc        = 1;

    FrameRate       = 100; //Milliseconds
    OldTime         = 0;

    Oscillate       = false;
}

void CAnimation::OnAnimate() {
    if(OldTime + FrameRate > SDL_GetTicks()) {
        return;
    }

    OldTime = SDL_GetTicks();

    CurrentFrame += FrameInc;

    if(Oscillate) {
        if(FrameInc > 0) {
            if(CurrentFrame >= MaxFrames) {
                FrameInc = -FrameInc;
            }
        }else{
            if(CurrentFrame <= 0) {
                FrameInc = -FrameInc;
            }
        }
    }else{
        if(CurrentFrame >= MaxFrames) {
            CurrentFrame = 0;
        }
    }
}

void CAnimation::SetFrameRate(int Rate) {
    FrameRate = Rate;
}

void CAnimation::SetCurrentFrame(int Frame) {
    if(Frame < 0 || Frame >= MaxFrames) return;

    CurrentFrame = Frame;
}

int CAnimation::GetCurrentFrame() {
    return CurrentFrame;
}


//------------------------------------------------------

bool CAnimation::onHit() {

    if(OldTime + FrameRate > SDL_GetTicks()) {
        //return;
    }

    OldTime = SDL_GetTicks();

    CurrentFrame += FrameInc;


    if(CurrentFrame >= hitFrames) {
        CurrentFrame = 0;
    }

}

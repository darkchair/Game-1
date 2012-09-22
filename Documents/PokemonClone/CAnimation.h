#ifndef _CANIMATION_H_
    #define _CANIMATION_H_

#include <SDL/SDL.h>

class CAnimation {
    public:
        int    CurrentFrame;

        int     FrameInc;

    public:
        int     FrameRate; //Milliseconds

        long    OldTime;

    public:
        int    MaxFrames;

        int     hitFrames;

        bool    Oscillate;

    public:
        CAnimation();

        void OnAnimate();

    public:
        void SetFrameRate(int Rate);

        void SetCurrentFrame(int Frame);

        int GetCurrentFrame();


        bool onHit();
};

#endif

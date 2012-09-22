#ifndef CFPS_H_INCLUDED
#define CFPS_H_INCLUDED

#include <SDL/SDL.h>

class CFPS {
    public:
        static CFPS FPSControl;

    private:
        int     OldTime;
        int     LastTime;

        float     SpeedFactor;

        int    NumFrames;
        int     Frames;

    public:
        CFPS();

        void    OnLoop();

    public:
        int     GetFPS();

        float   GetSpeedFactor();
};

#endif // CFPS_H_INCLUDED

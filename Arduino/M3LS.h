/*
*/

#ifndef M3LS_h
#define M3LS_h

#include "Arduino.h"

class M3LS{
    public:
        M3LS(int X_SS, int Y_SS, int Z_SS);
        //Function declarations
    private:
        int _xSS;
        int _ySS;
        int _zSS;
};

#endif

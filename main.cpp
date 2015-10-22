#include "MasterControl.h"
#include <SDL.h>
#include <math.h>
#include <iostream>
int main(int argc, char **argv){
    MasterControl Engine;
    while (Engine.GameRunning){
        Engine.Update();
    }
    return 0;
}

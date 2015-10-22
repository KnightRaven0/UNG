#ifndef MASTERCONTROL_H
#define MASTERCONTROL_H

#include <vector>

#include "GameState.h"
#include "GameEngine.h"
#include "MainMenu.h"

class MasterControl{
    public:
        MasterControl();
        ~MasterControl();
        void Update();

        void PushState(GameState* State);
        void PopState();

        Renderer* GetRenderer();        //Debug Function To be removed before release

        bool GameRunning;
    protected:
        Renderer Render;
        std::vector<GameState*> GameStates;
};

#endif // MASTERCONTROL_H

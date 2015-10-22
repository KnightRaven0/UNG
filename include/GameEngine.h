#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "GameState.h"
#include "Interface.h"
#include "Renderer.h"
#include "Options.h"
#include "Timer.h"
#include "UserInterface.h"
#include "MainMenu.h"

class MasterControl;

class GameEngine : public GameState{
    public:
        GameEngine(Renderer* RenderEngine);

        void Update(MasterControl* Control);

        void UpdateObjects();
        void HandleEvents(MasterControl* Control);
        void Draw();
        void CollisionDetection();
        void ForceCollisionCheck(Collidable* Collide);

        void Pause();
        void Resume();

        Interface Inter;
        UserInterface UI;

    protected:
        Renderer* Render;
        Options Option;

        Timer MovementTimer;
        Timer CollisionTimer;
        Timer RenderTimer;

        bool Debugging;
        bool W, S, A, D;
        bool V, H;
        bool UpdateAnim;

        int8_t ActivePC = 0;
        int8_t GameState = 0;
};

#endif // GAMEENGINE_H

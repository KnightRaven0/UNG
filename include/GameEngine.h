#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <Interface.h>
#include <Renderer.h>

class GameEngine{
    public:
        GameEngine();
        ~GameEngine();
        void Update();
        void HandleEvents();
        void HandleMovement(char Key, bool Press);
        void RenderGame();

        bool Running;
        Interface _Interface;
        Renderer Render;

    protected:
        bool Debugging;
};

#endif // GAMEENGINE_H

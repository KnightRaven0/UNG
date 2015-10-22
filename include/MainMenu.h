#ifndef MAINMENU_H
#define MAINMENU_H

#include <vector>
#include <SDL.h>

#include "GameState.h"
#include "Button.h"
#include "Renderer.h"
#include "Sprite.h"

class MasterControl;

class MainMenu : public GameState{
    public:
        MainMenu(Renderer* RenderEngine);
        ~MainMenu();

        void Update(MasterControl* Control);
        void Draw();
        void HandleEvents(MasterControl* Control);

    protected:
        Button ButtonStart;
        Button ButtonExit;

        Renderer* Render;
};

#endif // MAINMENU_H

#include "MainMenu.h"
#include "GameEngine.h"
#include "MasterControl.h"

MainMenu::MainMenu(Renderer* RenderEngine) : ButtonStart(RenderEngine->GetWidth() / 2, 400, RenderEngine->GetTexture("Resources//Textures//Button.png"), RenderEngine->LoadText("Start", "Airstream.ttf", 27, SDL_Color{255,255,255})),
                                             ButtonExit(RenderEngine->GetWidth() / 2, 600, RenderEngine->GetTexture("Resources//Textures//Button.png"), RenderEngine->LoadText("Exit", "Airstream.ttf", 27, SDL_Color{0,255,255})){
    Render = RenderEngine;
}

MainMenu::~MainMenu(){

}
void MainMenu::Update(MasterControl* Control){
    HandleEvents(Control);
    Draw();
}
void MainMenu::Draw(){
    Render->RenderStart();
    Render->RenderSprites(ButtonStart.GetSprites());
    Render->RenderSprites(ButtonExit.GetSprites());
    Render->RenderFinish();
}
void MainMenu::HandleEvents(MasterControl* Control){
    SDL_Event Events;
    while(SDL_PollEvent(&Events)){
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (Events.type == SDL_MOUSEMOTION){
            ButtonStart.CheckWithin(x, y);
            ButtonExit.CheckWithin(x, y);
        }
        if(Events.type == SDL_MOUSEBUTTONDOWN && Events.button.button == SDL_BUTTON_LEFT){
            if (ButtonStart.CheckWithin(x, y)){
                Control->PushState(new GameEngine(Render));
            }
        }
        if(Events.type == SDL_MOUSEBUTTONDOWN && Events.button.button == SDL_BUTTON_LEFT){
            if (ButtonExit.CheckWithin(x, y)){
                Control->GameRunning = false;
            }
        }
    }
}

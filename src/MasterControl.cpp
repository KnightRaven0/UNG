#include "MasterControl.h"

MasterControl::MasterControl() : Render("Un-Named Game", 30, 30 , 1280, 720){
    GameRunning = true;
    PushState(new MainMenu(&Render));
}

MasterControl::~MasterControl(){
    for (int i; i < GameStates.size(); i++){
        delete[] GameStates[i];
    }
}
void MasterControl::Update(){
    GameStates.back()->Update(this);
}
void MasterControl::PushState(GameState* State){
	if (!GameStates.empty()){
		GameStates.back()->Pause();
	}
	GameStates.push_back(State);
}
Renderer* MasterControl::GetRenderer(){
    return &Render;
}
void MasterControl::PopState(){
    if (!GameStates.empty()){
        GameStates.pop_back();
        if (!GameStates.empty()){
            GameStates.back()->Resume();
        }
    }
}

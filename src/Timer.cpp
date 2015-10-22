#include "Timer.h"

#include <SDL.h>
#include <iostream>

bool Timer::Paused;
float Timer::UsedGameTime;
int Timer::AssumedGameTime;
float Timer::GameSpeed;

Timer::Timer(const int Delay, bool TrueTime){    // -1 Delay always returns true. Be careful with WHILE loops involving timers.
    Time = UsedGameTime;
    DeltaTime = Delay;
    LocalPause = false;
}
void Timer::InitializeTime(){
    AssumedGameTime = SDL_GetTicks();
    UsedGameTime = AssumedGameTime;
}
bool Timer::IsTime(){
    if (DeltaTime == -1)
        return true;
    if (LocalPause)
        return false;
    if (!TrueTime){
        if (UsedGameTime - Time > DeltaTime){
            Time += DeltaTime;
            return true;
        }
    }else{
        if (SDL_GetTicks() - Time > DeltaTime){
            Time += DeltaTime;
            return true;
        }
    }
    return false;
}
void Timer::Pause(){
    if (!LocalPause){
        LocalPause = true;
        Time = UsedGameTime - Time;
    }
}
void Timer::Resume(){
    if (LocalPause){
        LocalPause = false;
        Time += UsedGameTime;
    }
}
int Timer::GetTicks(){
    return UsedGameTime;
}
void Timer::SetGameSpeed(const float NewSpeed){
    GameSpeed = NewSpeed;
}
void Timer::Update(){
    if (!Paused && (SDL_GetTicks() != AssumedGameTime)){
        UsedGameTime += (SDL_GetTicks() - AssumedGameTime) * GameSpeed;
        AssumedGameTime = SDL_GetTicks();
    }
}
void Timer::PauseGame(){
    Paused = true;
}
void Timer::UnpauseGame(){
    Paused = false;
}

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>

#include <GameEngine.h>

int main(int argc, char **argv){
    GameEngine Engine;

	Engine._Interface.CreatePlayableCharacter(100, 100);
    //GameLoader.LoadLevel(int SaveID, Engine)

	while (Engine.Running){
        Engine.Update();
	}
//	Engine.~GameEngine();
    return 0;
}

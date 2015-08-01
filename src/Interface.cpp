#include <SDL.h>
#include <windows.h>

#include "Interface.h"
#include "FireBall.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Renderer.h"

Interface::Interface(Renderer* _Renderer){
    Render = _Renderer;
    FireBalls.reserve(100);
}
Interface::~Interface(){
    Render = nullptr;
    FireBalls.clear();
    Characters.clear();
    PlayableCharacters.clear();
}
void Interface::CreateFireBall(float X, float Y, int Intel, int Wit, double Angle, int ChargeTime){
    FireBalls.push_back(FireBall(GetNewID(), X,Y, Intel, Wit, Angle, ChargeTime, Render->GetTexture("Resources//Textures//FireBall2.png")));
}
void Interface::CreatePlayableCharacter(float PosX, float PosY){
    PlayableCharacters.push_back(Character(GetNewID(), Render->GetTexture("Resources//Textures//CharacterSpriteSheet.png"),PosX, PosY));
}
std::vector<Particle> Interface::GetAllParticles(){
    std::vector<Particle> Particles;
    for (int i = 0; i < FireBalls.size(); i++){
        std::vector<Particle> p = FireBalls[i].GetParticles();
        Particles.reserve(Particles.size() + p.size());
        Particles.insert(Particles.end(), p.begin(), p.end());
    }
    return Particles;
}
std::vector<Sprite> Interface::GetAllSprites(){
    std::vector<Sprite> Sprites;
    int Size = FireBalls.size();
    for (int i = 0; i < Size; i++){
        Sprites.push_back(FireBalls[i].GetSprite());
    }
    return Sprites;
}
std::vector<AnimatedSprite> Interface::GetAllAnims(){       //Contains a memory leak
    std::vector<AnimatedSprite> Anims;
    int Size = Characters.size();
    for (int i = 0; i < Size; i ++){
        Anims.push_back(Characters[i].GetAnimation());
    }
    Size = PlayableCharacters.size();
    for (int i = 0; i < Size; i ++){
        Anims.push_back(PlayableCharacters[i].GetAnimation());
    }
    return Anims;
}
std::vector<FireBall>& Interface::GetAllFireBalls(){
    return FireBalls;
}
std::vector<Character>& Interface::GetPCs(){
    return PlayableCharacters;
}
int Interface::GetNewID(){
    return NextID++;
}

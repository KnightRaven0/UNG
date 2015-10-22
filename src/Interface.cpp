#include <SDL.h>
#include <windows.h>
#include <iostream>
#include <string>

#include "Interface.h"

Interface::Interface(Renderer* _Renderer){
    Render = _Renderer;
    Spells.reserve(100);
    DamageNumbers.reserve(100);
    int EmptyMap[10][10];
    for (int x = 0; x < 10; x++){
        for (int y = 0; y < 10; y++){
            EmptyMap[x][y] = 0;
        }
    }
    Chunks.reserve(10);
    std::vector<MapChunk> Temp;
    for (int i = 0; i < 10; i++){
        Chunks[i].reserve(10);
        Chunks.push_back(Temp);
    }
    Chunks[0].emplace_back(0, 0, EmptyMap, Render);
}
Interface::~Interface(){
    for (int i = 0; i < Spells.size(); i++)
        delete Spells[i];
    Spells.clear();
    NonPlayerChars.clear();
    Chunks.clear();
    PlayableCharacters.clear();
    Render = nullptr;
}
void Interface::CastSpell(Character* Actor, int ChargeTime){
    if (Actor->GetCurrentSpellID() == 1){
        Spells.push_back(new FireBall(Actor, ChargeTime, Render->GetTexture("Resources//Textures//FireBall2.png")));
    }
}
void Interface::CreatePlayableCharacter(float PosX, float PosY){
    PlayableCharacters.emplace_back(Render->GetTexture("Resources//Textures//CharacterSpriteSheet.png"),PosX, PosY, this);
}
void Interface::CreateCharacter(float PosX, float PosY){
    NonPlayerChars.emplace_back(Render->GetTexture("Resources//Textures//CharacterSpriteSheet.png"),PosX, PosY, this);
}
void Interface::CreateDamageNumber(float X, float Y, float Number, int8_t Type){    //0 = Damage, 1 = Heal, 2 = SetHealth, 3 = SpentMana, 4 = RestoredMana, 5 = SetMana
    SDL_Color C;
    switch (Type){
    case 0:
        C.r = 200;
        C.g = 20;
        C.b = 50;
        break;
    case 1:
        C.r = 20;
        C.g = 200;
        C.b = 70;
        break;
    case 2:
        C.r = 0;
        C.g = 255;
        C.b = 0;
        break;
    case 3:
        C.r = 5;
        C.g = 10;
        C.b = 100;
        break;
    case 4:
        C.r = 20;
        C.g = 40;
        C.b = 220;
        break;
    case 5:
        C.r = 0;
        C.g = 0;
        C.b = 255;
        break;
    default:
        C.r = 0;
        C.g = 0;
        C.b = 0;
        break;
    }
    int Size = sqrt(5 * Number) + 15;
    DamageNumbers.push_back(new DamageNumber(X, Y, Render->LoadText(std::to_string((int)Number), "Airstream.ttf", Size, C)));
}
void Interface::PreserveParticles(std::vector<Particle> NewParticles){
    Particles.reserve(Particles.size() + NewParticles.size());
    Particles.insert(Particles.end(), NewParticles.begin(), NewParticles.end());
}

std::vector<Character>& Interface::GetPCs(){
    return PlayableCharacters;
}
std::vector<Character>& Interface::GetNPCs(){
    return NonPlayerChars;
}
std::vector<Particle>& Interface::GetStrayParticles(){
    return Particles;
}
std::vector<DamageNumber*>& Interface::GetDamageNumbers(){
    return DamageNumbers;
}

std::vector<Particle> Interface::GetAllParticles(){
    std::vector<Particle> Particles;
    for (int i = 0; i < Spells.size(); i++){
        std::vector<Particle> p = Spells[i]->GetParticles();
        Particles.reserve(Particles.size() + p.size());
        Particles.insert(Particles.end(), p.begin(), p.end());
    }
    return Particles;
}
std::vector<Renderable*> Interface::GetRenderables(){
    std::vector<Renderable*> Renderables;
    int Size = DamageNumbers.size();
    for (int i = 0; i < Size; i++){
        Renderables.push_back(DamageNumbers[i]);
    }
    return Renderables;
}
std::vector<Sprite*> Interface::GetMapSprites(){
    std::vector<Sprite*> Sprites;
    int Size = Chunks.size();
    for (int y = 0; y < Size; y++){
        for (int x = 0; x < Chunks[y].size(); x ++){
            std::vector<Sprite*> s = Chunks[x][y].GetSprites();
            Sprites.reserve(Sprites.size() + s.size());
            Sprites.insert(Sprites.end(), s.begin(), s.end());
        }
    }
    return Sprites;
}
std::vector<Sprite*> Interface::GetAllSprites(){
    std::vector<Sprite*> Sprites;
    int Size = Spells.size();
    for (int i = 0; i < Size; i++){
        Sprites.push_back(Spells[i]->GetSprite());
    }
    Size = NonPlayerChars.size();
    for (int i = 0; i < Size; i ++){
        Sprites.push_back(NonPlayerChars[i].GetAnimation());
    }
    Size = PlayableCharacters.size();
    for (int i = 0; i < Size; i ++){
        Sprites.push_back(PlayableCharacters[i].GetAnimation());
    }
    return Sprites;
}
std::vector<Spell*>& Interface::GetSpells(){
    return Spells;
}
std::vector<Collidable*> Interface::GetCollidables(){
    std::vector<Collidable*> Collides;
    int Size = PlayableCharacters.size();
    for (int i = 0; i < Size; i++){
        if (dynamic_cast<Collidable*>(&PlayableCharacters[i]) != NULL){
            Collides.push_back(&PlayableCharacters[i]);
        }
    }
    Size = NonPlayerChars.size();
    for (int i = 0; i < Size; i++){
        if (dynamic_cast<Collidable*>(&NonPlayerChars[i]) != NULL){
            Collides.push_back(&NonPlayerChars[i]);
        }
    }
    Size = Spells.size();
    for (int i = 0; i < Size; i++){
        Spell*& Refer = Spells[i];
        if (dynamic_cast<Collidable*>(Refer) != NULL){
            Collides.push_back(dynamic_cast<Collidable*>(Refer));
        }
    }
    return Collides;
}

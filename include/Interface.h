#ifndef INTERFACE_H
#define INTERFACE_H

#include <vector>

#include "AnimatedSprite.h"
#include "FireBall.h"
#include "Sprite.h"
#include "Character.h"
#include "Renderer.h"

class Interface{
    public:
        Interface(Renderer* _Renderer);
        ~Interface();

        Renderer* Render;

        void CreateFireBall(float X, float Y, int Intel, int Wit, double Angle, int ChargeTime);
        void CreateCharacter(float PosX, float PosY);
        void CreatePlayableCharacter(float PosX, float PosY);

        std::vector<Particle> GetAllParticles();
        std::vector<Sprite> GetAllSprites();
        std::vector<AnimatedSprite> GetAllAnims();
        std::vector<FireBall>& GetAllFireBalls();
        std::vector<Character>& GetNPCs();
        std::vector<Character>& GetPCs();

        int8_t ActivePC = 0;


    protected:
        std::vector<FireBall> FireBalls;
        std::vector<Character> Characters;
        std::vector<Character> PlayableCharacters;

        int GetNewID();
        int NextID = 100;
};
#endif // INTERFACE_H

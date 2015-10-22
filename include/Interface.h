#ifndef INTERFACE_H
#define INTERFACE_H

#include <vector>

#include "Renderable.h"
#include "AnimatedSprite.h"
#include "FireBall.h"
#include "Sprite.h"
#include "Character.h"
#include "Renderer.h"
#include "Spell.h"
#include "MapChunk.h"
#include "DamageNumber.h"

class Interface{
    public:
        Interface(Renderer* _Renderer);
        ~Interface();

        Renderer* Render;

        void CastSpell(Character* Actor, int ChargeTime);
        void CreateCharacter(float PosX, float PosY);
        void CreatePlayableCharacter(float PosX, float PosY);
        void CreateDamageNumber(float X, float Y, float Damage, int8_t Type);
        void PreserveParticles(std::vector<Particle> Particles);

        std::vector<Particle> GetAllParticles();
        std::vector<Sprite*> GetAllSprites();
        std::vector<Sprite*> GetMapSprites();
        std::vector<Collidable*> GetCollidables();
        std::vector<Renderable*> GetRenderables();

        std::vector<Character>& GetNPCs();
        std::vector<Character>& GetPCs();
        std::vector<Spell*>& GetSpells();
        std::vector<Particle>& GetStrayParticles();
        std::vector<DamageNumber*>& GetDamageNumbers();

    protected:
        std::vector<Spell*> Spells;
        std::vector<Character> NonPlayerChars;
        std::vector<Character> PlayableCharacters;
        std::vector<std::vector<MapChunk>> Chunks;
        std::vector<Particle> Particles;
        std::vector<DamageNumber*> DamageNumbers;
};
#endif // INTERFACE_H

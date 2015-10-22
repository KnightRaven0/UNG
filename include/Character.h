#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

#include "AnimatedSprite.h"
#include "Vector2.h"
#include "Collidable.h"
#include "Identification.h"
#include "Timer.h"
#include "Item.h"

class Interface;

class Character : public Collidable , public Identification{
    public:
        Character(SDL_Texture* CharacterTexture, float PosX, float PosY, Interface* CreationInterface);
        ~Character();

        void Rotate(double RotateAmount);
        void MoveForward(float PercentSpeed);

        AnimatedSprite* GetAnimation(int AnimIndex = -1);
        void SetAnimation(int Direction);
        SDL_Rect* GetCollisionRect();
        void Update();

        float GetHealth();
        float GetMaxHealth();
        void DoDamage(float DamageDone);
        void Heal(float HealthRestored);
        void SetHealth(float NewHealth);

        float GetMana();
        float GetMaxMana();
        void SpendMana(float SpentMana);
        void RestoreMana(float AmountRestored);
        void SetMana(float NewMana);

        bool IsAlive();
        bool HasMana(float ManaAmount);
        std::string GetFirstName();
        std::string GetSurName();
        std::string GetFullName();

        int GetCurrentSpellID();

        double GetAngle();
        int BusyTimer;

        int GetStr();
        int GetCon();
        int GetEnd();

        int GetInt();
        int GetWit();
        int GetWil();

        int GetDex();
        int GetAgi();
        int GetChr();

    protected:
        //Stats
        int Str;    //Melee Damage, Carry Weight, Character Weight
        int StrMod;
        int Con;    //Damage Resistance, Knockdown resistance, Elemental Resistance
        int ConMod;
        int End;    //Tiring Factor, Sustain Factor, Total Life
        int EndMod;

        int Int;    //Governing Factor, Methodical Preperation, Pattern Solving
        int IntMod;
        int Wit;    //Clever Conversationalist, Instinct Magic, Tactical Resourcefulness
        int WitMod;
        int Wil;    //Mind Resistance, Religious Factor,
        int WilMod;

        int Dex;    //Balance factor, Reaction Time, Motion Speed
        int DexMod;
        int Agi;    //Footspeed, Manurverability, Traversable Terrain
        int AgiMod;
        int Chr;    //People Skills, Price Negotiation, Trust, Loyalty
        int ChrMod;

        //Characteristics
        std::string Name, Surname;
        int8_t Race;
        int8_t BirthSign;

        float Health, MaxHealth;
        float Mana, MaxMana;
        float MaxSpeed = 250;
        float Acceleration = 1;
        float DeltaX, DeltaY;

        std::vector<int> KnownSpells;
        int CurrentSpellID;

        Item* Helm;
        Item* Chest;
        Item* Legs;
        Item* Boots;
        Item* LeftHand;
        Item* RightHand;
        Item* LeftArm;
        Item* RightArm;

        std::vector<Item*> Inventory;

        float HeldWeight;

        //Instrinsic Data
        Timer RegenNumberTimer;
        Timer MovementTimer;
        Timer RegenTimer;
        float HealthRegen = .05;
        float ManaRegen = .05;
        Interface* Inter;
        std::vector<AnimatedSprite> Anims;  //N, S, E, W, NE, NW, SW, SE
        int ActiveAnim;                     //0, 1, 2, 3, 4 , 5 , 6 , 7
        Vector2 CharacterPosition;
        double CharacterAngle;

        //Temporary Data
        float HealthPastSec;
        float ManaPastSec;
};

#endif // CHARACTER_H

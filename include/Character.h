#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

#include "AnimatedSprite.h"
#include "Vector2.h"

class Character{
    public:
        Character(int NewID, SDL_Texture* CharacterTexture, float PosX, float PosY);
        ~Character();

        AnimatedSprite& GetAnimation(int AnimIndex = -1);
        void SetAnimation(int Direction);
        void Update();

        double GetAngle();
        int ID;
        int BusyTimer;

    protected:
        //Stats
        int Str;    //Melee Damage, Carry Weight, Character Weight
        int Con;    //Damage Resistance, Knockdown resistance, Elemental Resistance
        int End;    //Tiring Factor, Sustain Factor, Total Life

        int Int;    //Governing Factor, Methodical Preperation, Pattern Solving
        int Wit;    //Clever Conversationalist, Instinct Magic, Tactical Resourcefulness
        int Wil;    //Mind Resistance, Religious Factor,

        int Dex;    //Balance factor, Reaction Time, Motion Speed
        int Agi;    //Footspeed, Manurverability,
        int Chr;    //People Skills, Price Negotiation, Trust, Loyalty

        //Characteristics
        std::string Name, Surname;
        int8_t Race;
        int8_t BirthSign;

        float Health, MaxHealth;
        float Mana, MaxMana;
        float Speed;

        std::vector<AnimatedSprite> Anims;  //N, S, E, W, NE, NW, SW, SE
        int ActiveAnim;                     //0, 1, 2, 3, 4 , 5 , 6 , 7
};

#endif // CHARACTER_H

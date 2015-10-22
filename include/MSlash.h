#ifndef MSLASH_H
#define MSLASH_H

#include "MeleeAttack.h"

class MSlash : public MeleeAttack{
    public:
        MSlash(float X, float Y, Item* Weapon, Character* Parent);
        ~MSlash();

        SDL_Rect* GetCollisionRect();
        void Update(float X, float Y);

    protected:
        double Angle;
        double Arc;
        bool LeftToRight;
        bool HorizontalOrVertical;
};

#endif // MSLASH_H

#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <SDL.h>
#include <vector>

#define REASON_ONLYONCE     0x01
#define REASON_PERMANENT    0x02
#define REASON_ONLYSPELLS   0x04

class Collidable{
    public:
        Collidable(){}
        Collidable(int ParentID, bool Temporary = true);
        virtual ~Collidable();
        virtual SDL_Rect* GetCollisionRect() = 0;
        virtual double GetAngle(){return NULL;}
        virtual void Collided(){}
        void AddIgnore(int ID, uint8_t Reason);
        void RemoveIgnore(int ID, uint8_t SpecificReason = 0);
        bool ShouldIgnore(Collidable& Obj);

    protected:
        bool IgnoreAll;
        std::vector<int> IgnoreList;
        std::vector<uint8_t> IgnoreType;
        static std::vector<int> GlobalIgnoreList;
        static std::vector<uint8_t> GlobalIgnoreType;
};

#endif // COLLIDABLE_H

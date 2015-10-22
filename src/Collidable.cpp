#include "Collidable.h"
#include "Identification.h"
#include <iostream>

Collidable::Collidable(int ParentID, bool Temporary) : IgnoreAll(){
    if (ParentID != -1 && ParentID != NULL){
        if (Temporary)
            AddIgnore(ParentID, REASON_ONLYONCE);
        else
            AddIgnore(ParentID, REASON_PERMANENT);
    }
}
Collidable::~Collidable(){}
void Collidable::AddIgnore(int ID, uint8_t Reason){
    IgnoreList.push_back(ID);
    IgnoreType.push_back(Reason);
}
void Collidable::RemoveIgnore(int ID, uint8_t SpecificReason){
    int Size = IgnoreList.size();
    for (int i = 0; i < Size; i++){
        if (IgnoreList[i] == ID){
            IgnoreList.erase(IgnoreList.begin() + i);
            IgnoreType.erase(IgnoreType.begin() + i);
        }
    }
}
bool Collidable::ShouldIgnore(Collidable& Obj){
    //if (IgnoreAll == true)
    //    return true;
    bool Ignore = false;
    int ObjID;
    if (dynamic_cast<Identification*>(&Obj) != NULL){
        ObjID = dynamic_cast<Identification*>(&Obj)->GetID();
    }else
        return Ignore;
    int Size = IgnoreList.size();
    for (int i = 0; i < Size; i++){
        if (IgnoreList[i] == ObjID){
            if (IgnoreType[i] == REASON_ONLYONCE || IgnoreType[i] == REASON_PERMANENT)
                return true;
        }
    }
    return false;
}

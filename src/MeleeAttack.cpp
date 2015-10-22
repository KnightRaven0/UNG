#include "Character.h"
#include "MeleeAttack.h"

MeleeAttack::MeleeAttack(float X, float Y, Item* Weapon, Character* Parent) : Collidable(Parent->GetID()){

}
MeleeAttack::~MeleeAttack(){

}

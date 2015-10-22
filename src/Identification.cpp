#include "Identification.h"

int Identification::NextID = 1;

Identification::Identification(){
    ID = NextID++;
}
int Identification::GetID(){
    return ID;
}

#include "Vector2.h"

Vector2::Vector2(float X, float Y){
    x = X;
    y = Y;
}

void Vector2::SetX(float X){x = X;}
void Vector2::SetY(float Y){y = Y;}

float Vector2::GetX(){return x;}
float Vector2::GetY(){return y;}
int Vector2::GetIntX(){return (x > 0.0) ? (x + 0.5) : (x - 0.5);}
int Vector2::GetIntY(){return (y > 0.0) ? (y + 0.5) : (y - 0.5);}

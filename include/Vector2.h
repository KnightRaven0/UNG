#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2{
    public:
        Vector2(float X, float Y);

        void SetX(float X);
        void SetY(float Y);

        float GetX();
        float GetY();
        int GetIntX();
        int GetIntY();

    protected:
        float x, y;
};
#endif // VECTOR2_H

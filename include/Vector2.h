#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2{
    public:
        Vector2();
        Vector2(float X, float Y);
        virtual ~Vector2(){}

        void SetX(float X);
        void SetY(float Y);

        void ModX(float X);
        void ModY(float Y);

        float GetX();
        float GetY();
        int GetIntX();
        int GetIntY();

    protected:
        float x, y;
};
#endif // VECTOR2_H

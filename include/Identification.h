#ifndef IDENTIFICATION_H
#define IDENTIFICATION_H


class Identification
{
    public:
        Identification();

        int GetID();

    protected:
        static int NextID;
        int ID;
};

#endif // IDENTIFICATION_H

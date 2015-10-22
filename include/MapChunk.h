#ifndef MAPCHUNK_H
#define MAPCHUNK_H

#include <vector>

#include "Sprite.h"
#include "Renderer.h"

class MapChunk{
    public:
        MapChunk();
        MapChunk(int X, int Y, int Data[10][10], Renderer* Render);
        ~MapChunk();
        void CreateChunk(int X, int Y, int Data[10][10], Renderer* Render);
        std::vector<Sprite*> GetSprites();
        MapChunk& operator=(const MapChunk& Source);

    protected:
        std::vector<std::vector<Sprite*>> TextureData;
};

#endif // MAPCHUNK_H

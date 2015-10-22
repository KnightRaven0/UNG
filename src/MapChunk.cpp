#include <SDL.h>
#include <string>
#include <iostream>

#include "MapChunk.h"

MapChunk::MapChunk(){
    TextureData.reserve(10);
    for (int i = 0; i < 10; i++)
        TextureData[i].reserve(10);
}
MapChunk::MapChunk(int X, int Y, int Data[10][10], Renderer* Render){
    TextureData.reserve(10);
    for (int i = 0; i < 10; i++)
        TextureData[i].reserve(10);
    CreateChunk(X, Y, Data, Render);
}
MapChunk::~MapChunk(){
    for (int y = 0; y < 10; y++){
        for (int x = 0; x < 10; x++){
            delete TextureData[y][x];
        }
    }
}
void MapChunk::CreateChunk(int X, int Y, int Data[10][10], Renderer* Render){
    std::vector<Sprite*> Temp;
    for (int y = 0; y < 10; y++){
        Temp.clear();
        for (int x = 0; x < 10; x++){
            switch (Data[y][x]){
            case 0:
                Temp.push_back(new Sprite(Render->GetTexture("Resources//Textures//MapTextures//B000M800.bmp"), X + 128 * x, Y + 128 * y));
                break;
            default:
                break;
            }
        }
        TextureData.push_back(Temp);
    }
}
std::vector<Sprite*> MapChunk::GetSprites(){
    std::vector<Sprite*> Temp;
    for (int x = 0; x < 10; x++){
        for (int y = 0; y < 10; y++){
            Temp.push_back(TextureData[x][y]);
        }
    }
    return Temp;
}

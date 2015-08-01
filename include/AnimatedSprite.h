#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"

class AnimatedSprite : public Sprite{
    public:
        AnimatedSprite(SDL_Texture* AnimatedTexture, float X, float Y, int TexX, int TexY, int Row, int Column, int FrameHeight, int FrameWidth, int Delay,
                       int TotalFrames, bool Loop = true, bool HoldLast = false);
        ~AnimatedSprite();
        void Update();
        void Reset();
        void Pause();
        void Resume(bool Restart = false);

    protected:
        int Rows, Columns;
        int Height, Width;
        int Frame, MaxFrames;
        int FrameDelay, LogicalDelay, StartTime;
        bool Looping, Holding, Paused;
        int TextureX, TextureY;
};
#endif // ANIMATEDSPRITE_H

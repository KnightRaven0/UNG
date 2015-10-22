#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"
#include "Timer.h"

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
        int TextureX, TextureY;
        int Rows, Columns;
        int Height, Width;
        int Frame, MaxFrames;
        Timer AnimationTimer;
        bool Looping, Holding;
};
#endif // ANIMATEDSPRITE_H

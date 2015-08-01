#include <SDL.h>

#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(SDL_Texture* AnimatedTexture, float X, float Y, int TexX, int TexY, int Row, int Column, int FrameHeight, int FrameWidth, int Delay,
            int TotalFrames, bool Loop, bool HoldLast) : TextureX(TexX), TextureY(TexY), Rows(Row), Columns(Column),
            Height(FrameHeight), Width(FrameWidth), FrameDelay(Delay), MaxFrames(TotalFrames), Looping(Loop), Holding(HoldLast),
            Sprite(AnimatedTexture, X, Y){
    ClipingRect.x = TexX;
    ClipingRect.y = TexY;
    ClipingRect.h = FrameHeight;
    ClipingRect.w = FrameWidth;
    DestinationRect.h = FrameHeight;
    DestinationRect.w = FrameWidth;
    StartTime = SDL_GetTicks();
    LogicalDelay = Delay;
    Frame = 1;
}
AnimatedSprite::~AnimatedSprite(){

}

void AnimatedSprite::Update(){
    if (SDL_GetTicks() - StartTime > LogicalDelay && !Paused){
        LogicalDelay += FrameDelay;
        ClipingRect.x = (Frame % Columns * Width) + TextureX;
        ClipingRect.y = (Frame % Rows * Height) + TextureY;
        if (Holding && Frame == MaxFrames)
            return;
        if (Looping){
            if (Frame == MaxFrames)
                Frame = 1;
            else
                Frame += 1;
        }
    }
}
void AnimatedSprite::Pause(){
    Paused = true;
}
void AnimatedSprite::Resume(bool Restart){
    Paused = false;
    if (Restart)
        Reset();
}
void AnimatedSprite::Reset(){
    StartTime = SDL_GetTicks();
    LogicalDelay = FrameDelay;
    Frame = 1;
}

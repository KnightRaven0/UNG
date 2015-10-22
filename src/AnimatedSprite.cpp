#include <SDL.h>

#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(SDL_Texture* AnimatedTexture, float X, float Y, int TexX, int TexY, int Row, int Column, int FrameHeight, int FrameWidth, int Delay,
            int TotalFrames, bool Loop, bool HoldLast) : Sprite(AnimatedTexture, X, Y), TextureX(TexX), TextureY(TexY), Rows(Row), Columns(Column),
            Height(FrameHeight), Width(FrameWidth), MaxFrames(TotalFrames), AnimationTimer(Delay), Looping(Loop), Holding(HoldLast){
    ClipingRect.x = TexX;
    ClipingRect.y = TexY;
    ClipingRect.h = FrameHeight;
    ClipingRect.w = FrameWidth;
    DestinationRect.h = FrameHeight;
    DestinationRect.w = FrameWidth;
    Frame = 1;
    Origin.x = FrameWidth / 2;
    Origin.y = FrameHeight / 2;
}
AnimatedSprite::~AnimatedSprite(){

}

void AnimatedSprite::Update(){
    if (AnimationTimer.IsTime()){
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
    AnimationTimer.Pause();
}
void AnimatedSprite::Resume(bool Restart){
    AnimationTimer.Resume();
    if (Restart)
        Reset();
}
void AnimatedSprite::Reset(){
    Frame = 1;
}

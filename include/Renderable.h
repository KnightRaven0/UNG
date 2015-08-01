#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Vector2.h"

class Renderable : public Vector2{
    public:
        Renderable(SDL_Texture* RenderTexture, float X, float Y);

		SDL_Rect* GetDestination();
		SDL_Texture* GetTexture();

        void SetTexture(SDL_Texture* NewTexture);

    protected:
		bool Visible;
		SDL_Texture* Texture;
		SDL_Rect DestinationRect;
};
#endif

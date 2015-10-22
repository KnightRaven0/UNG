#ifndef SPRITE_H
#define SPRITE_H

#include "Renderable.h"

class Sprite : public Renderable {
	public:
		Sprite(SDL_Texture* SpriteTexture, float PosX, float PosY);
		~Sprite();

        SDL_Rect* GetDestination();
		SDL_Rect* GetCliping();
		SDL_Point* GetOrigin();
		double GetAngle();
		int GetHeight();
		int GetWidth();

		void SetCliping(int ClipX, int ClipY, int ClipW, int ClipH);
		void SetOrigin(int OriginX, int OriginY);
		void SetAngle(double NewAngle);
		void ScaleScale(float ScalesScale);
		void SetScale(float NewScale);

	protected:
		SDL_Rect ClipingRect;
		SDL_Point Origin;
		double Angle;

		float Scale;
};
#endif

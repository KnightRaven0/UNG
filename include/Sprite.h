#ifndef SPRITE_H
#define SPRITE_H

#include "Renderable.h"

class Sprite : public Renderable {
	public:
		Sprite(SDL_Texture* SpriteTexture, float PosX, float PosY);
		~Sprite();

        SDL_Rect* GetDestination();
		SDL_Rect* GetCliping();
		SDL_Point* GetOrgin();
		double GetAngle();
		int GetHeight();
		int GetWidth();

		void SetCliping(int ClipX, int ClipY, int ClipH, int ClipW);
		void SetOrgin(int OrginX, int OrginY);
		void SetAngle(double NewAngle);
		void ScaleScale(float ScalesScale);
		void SetScale(float NewScale);

	protected:
		SDL_Rect ClipingRect;
		SDL_Point Orgin;
		double Angle;

		float Scale;

		void UpdateDestination();
};
#endif

#ifndef RENDERER
#define RENDERER

#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Particle.h"

#include <vector>

class Renderer{
	public:
		Renderer(std::string Name, int PosX, int PosY, int ScreenWidth, int ScreenHeight);
		~Renderer();

		void RenderObj(SDL_Texture *Texture, SDL_Renderer *Renderer, SDL_Rect *Destination, SDL_Rect *Cliping, double Angle, SDL_Point* Orgin);
		void RenderObj(SDL_Texture *Texture, SDL_Renderer *Renderer, SDL_Rect *Destination, SDL_Rect *Cliping);

        SDL_Texture* LoadTexture(const std::string &Path);
        SDL_Texture* GetTexture(const std::string &Path);

		void RenderStart();
		void RenderSprites(std::vector<Sprite> Sprites);
		void RenderSprite(Sprite _Sprite);
		void RenderParticles(std::vector<Particle> Particles);
		void RenderAbles(std::vector<Renderable> Renderables);
		void RenderAnim(AnimatedSprite Animation);
		void RenderAnims(std::vector<AnimatedSprite> Animations);
		void RenderFinish();

		SDL_Rect* CameraShift(SDL_Rect* TranslatedObj);

		void SetX(int NewX);
		void SetY(int NewY);
		int GetX();
		int GetY();

		void SetWidth(int NewWidth);
		void SetHeight(int NewHeight);
		int GetHeight();
		int GetWidth();

	protected:
	    std::vector<SDL_Texture*> Textures;
	    std::vector<std::string> Paths;

		SDL_Window* Window;
		SDL_Renderer* Render;
		SDL_Point Camera;
};
#endif

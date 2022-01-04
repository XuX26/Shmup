#pragma once
#include <string>
#include <SDL_surface.h>
#include <SDL_render.h>

class Sprite
{
protected:
	SDL_Texture* _spriteImage = nullptr;
	SDL_Rect _spriteRect = { 0, 0, 0, 0 };
public:
	Sprite() = delete;
	Sprite(SDL_Texture* _spriteImage);
	Sprite(const Sprite&) = delete;
	Sprite(Sprite&&) = delete;
	Sprite& operator=(const Sprite&) = delete;
	~Sprite();

	void Render(SDL_Renderer* screenRenderer, int posX, int posY);
	void Render(SDL_Renderer* screenRenderer, int posX, int posY, double orientation);

	int GetWidth() const;
	int GetHeight() const;
};
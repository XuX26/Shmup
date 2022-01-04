#include "Sprite.h"
#include <SDL.h>

Sprite::Sprite(SDL_Texture* spriteImage): _spriteImage(spriteImage)
{
    SDL_QueryTexture(spriteImage, NULL, NULL, &_spriteRect.w, &_spriteRect.h);
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(_spriteImage);
}

void Sprite::Render(SDL_Renderer* screenRenderer, int posX, int posY)
{
    SDL_Rect rect = { posX - (_spriteRect.w >> 1), posY - (_spriteRect.h >> 1), _spriteRect.w, _spriteRect.h };
    SDL_RenderCopy(screenRenderer, _spriteImage, NULL, &rect);
}

void Sprite::Render(SDL_Renderer* screenRenderer, int posX, int posY, double orientation)
{
    SDL_Rect rect = { posX - (_spriteRect.w >> 1), posY - (_spriteRect.h >> 1), _spriteRect.w, _spriteRect.h };
    SDL_RenderCopyEx(screenRenderer, _spriteImage, NULL, &rect, orientation, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
}

int Sprite::GetWidth() const
{
    return _spriteRect.w;
}

int Sprite::GetHeight() const
{
    return _spriteRect.h;
}

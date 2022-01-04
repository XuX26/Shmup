#include "Game.h"
#include "IGameEntity.h"
#include <SDL.h>
#include "CollisionManager.h"
#include "ICollidable.h"
#include <iostream>
#include <SDL_scancode.h>
#include "Font.h"
#include "SpriteFactory.h"
#include <time.h>
#include "SpaceShip.h"
#include "EntityFactory.h"
#include <memory>

Game::~Game() = default;
//std::unique_ptr<Game> Game::instance = nullptr;  //if no inline

bool Game::Init()
{
    EntityFactory::Init();
    Game::player = std::make_unique<Player>();
    Game::GetInstance()->AddEntity(EntityFactory::CreateSpaceShip(SpaceShipModel::player));
    Game::GetInstance()->AddEntity(EntityFactory::CreateSpaceShip(SpaceShipModel::fatty));
    Game::GetInstance()->AddEntity(EntityFactory::CreateSpaceShip(SpaceShipModel::medium));
    Game::GetInstance()->AddEntity(EntityFactory::CreateSpaceShip(SpaceShipModel::tiny));

	_isRunning = true;
	return true;
}

void Player::LoseHp(int damage)
{
    std::cout << "Lose HP player : "<< damage << std::endl;
    Game::GetInstance()->player->hp -= damage;
    if (hp <= 0)
        Game::GetInstance()->ResetGame();
}

void Game::ResetGame() {
    player->hp = 100;
    player->score = 0;
    //RemoveEntity
}

//void Game::AddScore(SpaceShipModel shipDestroyed) {
//    if (shipDestroyed == SpaceShipModel::tiny)
//        player->score += 50;
//    else if (shipDestroyed == SpaceShipModel::medium)
//        player->score += 100;
//    else if (shipDestroyed == SpaceShipModel::medium)
//        player->score += 200;
//}

void Game::Update(int deltaTime)
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            _isRunning = false;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            if(e.key.keysym.sym == SDLK_ESCAPE)
            {
                _isRunning = false;
            }
        }
    }

    if (_isRunning)
    {
        Game::collisionManager->Tick();
        if (_entitiesToRemove.size() > 0)
        {
            for (auto entity : _entitiesToRemove)
            {
                RemoveEntity(entity);
            }
            _entitiesToRemove.clear();
        }

        _delayEntityRemoval = true;
        for (auto entity : _entities)
        {
            entity->Update(deltaTime);
        }
        _delayEntityRemoval = false;
        if (_entitiesToRemove.size() > 0)
        {
            for (auto entity : _entitiesToRemove)
            {
                RemoveEntity(entity);
            }
            _entitiesToRemove.clear();
        }

    }
}

void Game::Render(SDL_Renderer* screenRenderer)
{
	if (_isRunning)
    {
        _delayEntityRemoval = true;
        for (auto entity : _entities)
        {
            entity->Render(screenRenderer);
        }
        _delayEntityRemoval = false;
    }

#if _DEBUG
    std::shared_ptr<Font> font = SpriteFactory::GetFont("arial.ttf", 24);
    SDL_Color White = { 255, 255, 255 };
    char message[255];
    #ifndef WIN32
        snprintf(message, 255, "Entities: %zu", _entities.size());
    #else
        sprintf_s(message, 255, "Entities: %zu", _entities.size());
    #endif
    auto texture = font->CreateTextTexture(message, White, screenRenderer);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { 0, 480 - texH, texW, texH };
    SDL_RenderCopy(screenRenderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
#endif
}

void Game::Release()
{
    for (auto entity : _entities)
    {
        entity->Release();
    }
    _entities.clear();
}

bool Game::IsRunning() const
{
	return _isRunning;
}

Game* Game::GetInstance()
{
    if (instance == nullptr)
        instance = std::make_unique<Game>();
    return instance.get();
}

void Game::DestroyInstance()
{
    instance.reset();  // or = null ?
}

void Game::AddEntity(std::shared_ptr<IGameEntity> entity)
{
    _entities.insert(entity);
    if (std::dynamic_pointer_cast<ICollidable>(entity) != nullptr)
        Game::collisionManager->AddCollider(std::dynamic_pointer_cast<ICollidable>(entity));
}

void Game::RemoveEntity(std::shared_ptr<IGameEntity> entity)
{
    if (_delayEntityRemoval)
    {
        _entitiesToRemove.insert(entity);
        if (std::dynamic_pointer_cast<ICollidable>(entity) != nullptr)
            Game::collisionManager->RemoveCollider(std::dynamic_pointer_cast<ICollidable>(entity));
        return;
    }
    _entities.erase(entity);
}

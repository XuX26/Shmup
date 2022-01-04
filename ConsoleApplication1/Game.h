#pragma once
#include <SDL_render.h>
#include <set>
#include <memory>
#include <functional>
#include "CollisionManager.h"

class IGameEntity;
class Player;
class SpaceShip;

class Game 
{
private:
	static inline std::unique_ptr<Game> instance;
	//static inline std::unique_ptr<Player> player;

	
    bool _isRunning;

	std::set<std::shared_ptr<IGameEntity> > _entities;
	bool _delayEntityRemoval;
	std::set<std::shared_ptr<IGameEntity> > _entitiesToRemove;

public:
	static const int lenghtWindow = 640;
	static const int heightWindow = 480;
	std::unique_ptr<CollisionManager> collisionManager = std::make_unique<CollisionManager>();
	std::unique_ptr<Player> player;
	/*Game()
	{
		if (instance != nullptr)
			throw std::exception("déjà créé !");
		instance = std::unique_ptr<Game>(this);
	}*/
	Game() = default;
	~Game();
	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(const Game&) = delete;

	bool Init();
	void Release();

	//void AddScore(SpaceShipModel shipDestroyed);

	void Update(int deltaTime);

	void Render(SDL_Renderer* screenRenderer);

	bool IsRunning() const;

	static Game* GetInstance();
	static void DestroyInstance();

	void ResetGame();
	void AddEntity(std::shared_ptr<IGameEntity>);
	void RemoveEntity(std::shared_ptr<IGameEntity>);
};

class Player {
public:
	Player() = default;
	~Player() = default;
	Player(const Player& model) = delete;
	Player(Player&& moved) = delete;
	Player& operator=(const Player&) = delete;

	std::shared_ptr<SpaceShip> ship;
	int hp = 0;
	int lifeleft = 0;
	int score = 0;

	void LoseHp(int damage);
};
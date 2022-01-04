#pragma once
#include <memory>
#include "SpaceShip.h"
#include <SDL.h>

class SpaceShip;
class Bullet;
class Sprite;

class IController
{
public:
	IController() {};
	virtual ~IController() = default;
	IController(const IController&) = default;
	IController(IController&&) = default;
	IController& operator=(const IController&) = default;

	virtual void Move(std::shared_ptr<SpaceShip> ship, int deltaTime) = 0;
	virtual void Fire(std::shared_ptr<SpaceShip> ship) = 0;
};

class PlayerShip : public IController
{
public:
	const Uint8* state = SDL_GetKeyboardState(NULL);

	PlayerShip() {};
	virtual ~PlayerShip() = default;
	PlayerShip(const PlayerShip&) = default;
	PlayerShip(PlayerShip&&) = default;
	PlayerShip& operator=(const PlayerShip&) = default;

	virtual void Move(std::shared_ptr<SpaceShip> ship, int deltaTime) override;
	virtual void Fire(std::shared_ptr<SpaceShip> ship) override;
};

class EnemyShip : public IController
{
public:
	EnemyShip() {};
	virtual ~EnemyShip() = default;
	EnemyShip(const EnemyShip&) = default;
	EnemyShip(EnemyShip&&) = default;
	EnemyShip& operator=(const EnemyShip&) = default;

	virtual void Move(std::shared_ptr<SpaceShip> ship, int deltaTime) override;
	virtual void Fire(std::shared_ptr<SpaceShip> ship) override;
};


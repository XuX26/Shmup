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
#include "Bullet.h"
// need clean some include

SpaceShip::~SpaceShip()
{
	Release();
}

std::shared_ptr<SpaceShip> SpaceShip::Create()
{
	std::shared_ptr <SpaceShip> spaceship = std::make_shared<SpaceShip>();
	spaceship->_weakPtr = spaceship;
	return spaceship;
}

std::shared_ptr<IGameEntity> SpaceShip::GetSharedPtr()
{
	return _weakPtr.lock();
};

void SpaceShip::Init(const IGameEntityConfig* config)
{
	_config = dynamic_cast<const SpaceShipConfig*>(config);

	posX = _config->startPosX;
	posY = _config->startPosY;
	rotation = _config->startRotation;
	speed = _config->defaultSpeed;
	hp = _config->startHp;
	shipModel = _config->shipModel;
	shipModel == SpaceShipModel::player ?
		shipType = std::make_unique<PlayerShip>()
		: shipType = std::make_unique<EnemyShip>();
	shotMode = GetDefaultShotMode(shipModel);
	bulletType = GetDefaultBulletType(shipModel);
	_sprite = SpriteFactory::GetSprite(GetSpritePath(_config->shipModel));
}
BulletType SpaceShip::GetDefaultBulletType(SpaceShipModel shipModel)
{
	if (shipModel == SpaceShipModel::fatty)
		return BulletType::giga;
	else
		return BulletType::normal;
}

ShotMode SpaceShip::GetDefaultShotMode(SpaceShipModel shipModel)
{
	if (shipModel == SpaceShipModel::tiny)
		return ShotMode::TripleShot;
	else
		return ShotMode::SingleShot;
}

std::string SpaceShip::GetSpritePath(SpaceShipModel shipModel)
{
	if (shipModel == SpaceShipModel::player)
		return "ships/1.png";
	else if (shipModel == SpaceShipModel::fatty)
		return "ships/2.png";
	else if (shipModel == SpaceShipModel::medium)
		return "ships/3.png";
	else if (shipModel == SpaceShipModel::tiny)
		return "ships/4.png";
}

void SpaceShip::Release()
{
}

void SpaceShip::Update(int deltaTime)
{
	shipType->Move(_weakPtr.lock(), deltaTime);
	shipType->Fire(_weakPtr.lock());
}

void SpaceShip::Render(SDL_Renderer* screenRenderer)
{
	_sprite->Render(screenRenderer, posX, posY, rotation);
}

int SpaceShip::GetCollisionTag() const
{
	return (int)shipModel;
}

int SpaceShip::GetRadius() const
{
	return _sprite.get()->GetHeight()/2;
}

int SpaceShip::GetPositionX() const
{
	return posX;
}

int SpaceShip::GetPositionY() const
{
	return posY;
}

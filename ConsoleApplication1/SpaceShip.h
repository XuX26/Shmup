#pragma once
#include "IGameEntity.h"
#include <memory>
#include <functional>
#include "Sprite.h"
#include "SpriteFactory.h"
#include "IMovingObjects.h"
#include "ICollidable.h"
#include "Bullet.h"

//class Sprite; //to avoid include sprite.h

class IController;
enum class SpaceShipModel;
enum class ShotMode;

class SpaceShipConfig : public IGameEntityConfig
{
public:
	SpaceShipConfig() = default;
	SpaceShipConfig(SpaceShipModel shipModel, int PosX, int PosY,
		double rotation, int speed, int hp)
		: shipModel(shipModel), startPosX(PosX), startPosY(PosY),
		startRotation(rotation), defaultSpeed(speed), startHp(hp) {};
	virtual	~SpaceShipConfig() = default;
	SpaceShipConfig(const SpaceShipConfig&) = default;
	SpaceShipConfig(SpaceShipConfig&&) = default;
	SpaceShipConfig& operator=(const SpaceShipConfig&) = default;

	SpaceShipModel shipModel;
	int startPosX;
	int startPosY;
	double startRotation;
	int defaultSpeed;
	int startHp;
};

class SpaceShip : public IGameEntity, public ICollidable
{
public:
	SpaceShip() = default;
	virtual	~SpaceShip();
	SpaceShip(const SpaceShip&) = default;
	SpaceShip(SpaceShip&&) = default;
	SpaceShip& operator=(const SpaceShip&) = default;

	int posX;
	int posY;
	double rotation;
	int speed;
	int hp;
	std::shared_ptr<IController> shipType;
	SpaceShipModel shipModel;
	ShotMode shotMode;
	BulletType bulletType;


	static std::shared_ptr<SpaceShip> Create();

	//Legacy
	virtual std::shared_ptr<IGameEntity> GetSharedPtr() override;
	virtual void Init(const IGameEntityConfig* config) override;
	BulletType GetDefaultBulletType(SpaceShipModel shipModel);
	ShotMode GetDefaultShotMode(SpaceShipModel shipModel);
	virtual void Release() override;
	virtual void Update(int deltaTime) override;
	virtual void Render(SDL_Renderer* screenRenderer) override;

private:
	std::shared_ptr<Sprite> _sprite;
	std::weak_ptr<SpaceShip> _weakPtr;
	const SpaceShipConfig* _config;

	std::string GetSpritePath(SpaceShipModel shipModel);

	// Hérité via ICollidable
	virtual int GetCollisionTag() const override;
	virtual int GetRadius() const override;
	virtual int GetPositionX() const override;
	virtual int GetPositionY() const override;
};


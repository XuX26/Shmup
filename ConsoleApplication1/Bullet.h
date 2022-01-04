#pragma once
#include <memory>
#include "IGameEntity.h"
#include "Sprite.h"
#include "SpriteFactory.h"
#include "ICollidable.h"

class Sprite;

enum BulletType {
	normal,
	giga,
};

enum Dir {
	RightTop,
	Right,
	RightBot,
	LeftTop,
	Left,
	LeftBot
};

class BulletConfig : public IGameEntityConfig
{ //Collider Tag param
public:
	BulletConfig() = default;
	BulletConfig(BulletType type, int PosX, int PosY, Dir dir, ICollidable::ColliderTag colliderTag)
		: bulletType(type), startPosX(PosX), startPosY(PosY), dir(dir), colliderTag(colliderTag){};
	virtual	~BulletConfig() = default;
	BulletConfig(const BulletConfig&) = default;
	BulletConfig(BulletConfig&&) = default;
	BulletConfig& operator=(const BulletConfig&) = default;

	BulletType bulletType;
	int startPosX;
	int startPosY;
	Dir dir;
	ICollidable::ColliderTag colliderTag;

	//bool isPlayerShot;
};

class Bullet : public IGameEntity, public ICollidable
{
public:
	Bullet() {};
	~Bullet() = default;
	Bullet(const Bullet&) = default;
	Bullet(Bullet&&) = default;
	Bullet& operator=(const Bullet&) = default;

	BulletType type;
	Dir dir;
	int posX;
	int posY;
	int speed;
	int damage;
	ColliderTag colliderTag;

	virtual void Update(int deltaTime) override;
	virtual std::shared_ptr<IGameEntity> GetSharedPtr() override;

	void Init(const IGameEntityConfig* config);
	static std::shared_ptr<Bullet> Create();
	void Move(int deltaTime);

private:
	const BulletConfig* _config;
	std::weak_ptr<Bullet> _weakPtr;
	std::shared_ptr<Sprite> _sprite;
	void InitVar(BulletType type);

	// Hérité via IGameEntity
	virtual void Release() override;
	virtual void Render(SDL_Renderer* screenRenderer) override;

	// Hérité via ICollidable
	virtual int GetCollisionTag() const override;
	virtual int GetRadius() const override;
	virtual int GetPositionX() const override;
	virtual int GetPositionY() const override;
};


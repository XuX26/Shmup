#include "Bullet.h"
#include "ICollidable.h"
#include <iostream>

enum BulletType;
class BulletConfig;

void Bullet::Move(int deltaTime)
{
	std::cout << "Bullet move" << std::endl;
	if (dir == Dir::RightTop) {
		posX += deltaTime * speed / 100;
		posY += deltaTime * speed / 100;
	}
	else if (dir == Dir::Right) {
		posX += deltaTime * speed / 100;
	}
	else if (dir == Dir::RightBot) {
		posX += deltaTime * speed / 100;
		posY -= deltaTime * speed / 100;
	}
	else if (dir == Dir::LeftTop) {
		posX -= deltaTime * speed / 100;
		posY -= deltaTime * speed / 100;
	}
	else if (dir == Dir::Left) {
		posX -= deltaTime * speed / 100;
	}
	else if (dir == Dir::LeftBot) {
		posX -= deltaTime * speed / 100;
		posY += deltaTime * speed / 100;
	}
}

void Bullet::Init(const IGameEntityConfig* config) {
	_config = dynamic_cast<const BulletConfig*>(config);

	type = _config->bulletType;
	posX = _config->startPosX;
	posY = _config->startPosY;
	dir = _config->dir;
	colliderTag = _config->colliderTag;
	Bullet::InitVar(_config->bulletType);
}

std::shared_ptr<Bullet> Bullet::Create()
{
	std::shared_ptr <Bullet> bullet = std::make_shared<Bullet>();
	bullet->_weakPtr = bullet;
	return bullet;
}

void Bullet::InitVar(BulletType type)
{
	if (type == BulletType::normal)
	{
		speed = 25;
		damage = 25;
		_sprite = SpriteFactory::GetSprite("shots/3.png");
	}
	else if (type == BulletType::giga)
	{
		speed = 20;
		damage = 100;
		_sprite = SpriteFactory::GetSprite("shots/10.png");
	}
}

std::shared_ptr<IGameEntity> Bullet::GetSharedPtr()
{
	return _weakPtr.lock();
}

void Bullet::Release()
{
}

void Bullet::Update(int deltaTime)
{
	Move(deltaTime);
}

void Bullet::Render(SDL_Renderer* screenRenderer)
{
	_sprite->Render(screenRenderer, posX, posY, 0);
}

int Bullet::GetCollisionTag() const
{
	return (int)colliderTag;
}

int Bullet::GetRadius() const
{
	return _sprite.get()->GetHeight()/2;
}

int Bullet::GetPositionX() const
{
	return posX;
}

int Bullet::GetPositionY() const
{
	return posY;
}

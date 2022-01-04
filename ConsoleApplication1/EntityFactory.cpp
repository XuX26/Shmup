#include "EntityFactory.h"
#include "IGameEntity.h"
#include "SpaceShip.h"
#include "Game.h"
#include "Bullet.h"
#include "ICollidable.h"
#include "IMovingObjects.h"

void EntityFactory::Init() {
	if (instance == nullptr)
		instance = std::make_unique<EntityFactory>();
}


std::shared_ptr<IGameEntity> EntityFactory::CreateSpaceShip(SpaceShipModel shipModel)
{
	std::unique_ptr<SpaceShipConfig> config;
	std::shared_ptr<SpaceShip> ship = SpaceShip::Create();
	std::weak_ptr<SpaceShip> shipPtr = ship;

	if (shipModel == SpaceShipModel::player) {
		config = std::make_unique<SpaceShipConfig>(shipModel, 50, 25, 90, 12, 100);
		ship->Init(config.get());
		Game::GetInstance()->player->ship = ship;
		Game::GetInstance()->collisionManager->AddCollisionCallback(ship, 10, [shipPtr](std::shared_ptr<ICollidable> other) { //edit collider
			Game::GetInstance()->player->LoseHp(100);
			});
	}
	else if (shipModel == SpaceShipModel::fatty) {
		config = std::make_unique<SpaceShipConfig>(shipModel, 640, 150, -90, 8, 100);
		ship->Init(config.get());
		Game::GetInstance()->collisionManager->AddCollisionCallback(ship, 4, [shipPtr](std::shared_ptr<ICollidable> other) {
			Game::GetInstance()->RemoveEntity(std::dynamic_pointer_cast<IGameEntity>(other));
			//Game::GetInstance()->AddScore(shipModel);
			Game::GetInstance()->player->score += 200;
			Game::GetInstance()->RemoveEntity(shipPtr.lock());
			});
	}
	else if (shipModel == SpaceShipModel::medium) {
		config = std::make_unique<SpaceShipConfig>(shipModel, 640, 250, -90, 8, 50);
		ship->Init(config.get());
		Game::GetInstance()->collisionManager->AddCollisionCallback(ship, 4, [shipPtr](std::shared_ptr<ICollidable> other) { 
			Game::GetInstance()->RemoveEntity(std::dynamic_pointer_cast<IGameEntity>(other));
			Game::GetInstance()->player->score += 100;
			Game::GetInstance()->RemoveEntity(shipPtr.lock());
			});
	}
	else if (shipModel == SpaceShipModel::tiny) {
		config = std::make_unique<SpaceShipConfig>(shipModel, 640, 350, -90, 8, 25);
		ship->Init(config.get());
		Game::GetInstance()->collisionManager->AddCollisionCallback(ship, 4, [shipPtr](std::shared_ptr<ICollidable> other) { 
			Game::GetInstance()->RemoveEntity(std::dynamic_pointer_cast<IGameEntity>(other));
			Game::GetInstance()->player->score += 50;
			Game::GetInstance()->RemoveEntity(shipPtr.lock());
			});
	}
	if (ship != nullptr)
		return ship->GetSharedPtr();
}

std::shared_ptr<IGameEntity> EntityFactory::CreateBullet(std::shared_ptr<SpaceShip> ship, Dir dir)
{
	std::unique_ptr<BulletConfig> config;
	std::shared_ptr<Bullet> bullet;
	std::weak_ptr<Bullet> bulletPtr;
	bool isFromPlayer = (ship->shipModel == SpaceShipModel::player);
	ICollidable::ColliderTag colliderTag = SetBulletColliderTag(ship->shipModel);

	bullet = Bullet::Create();
	bulletPtr = bullet;

	config = std::make_unique<BulletConfig>(ship->bulletType, ship->posX, ship->posY, dir, colliderTag);
	bullet->Init(config.get());

	if (bullet->GetSharedPtr() != nullptr)
		return bullet->GetSharedPtr();
	//
}
//std::shared_ptr<IGameEntity> EntityFactory::CreateBullet(ShotMode shotMode, BulletType bulletType, bool isPlayerShot)
//{
//	std::unique_ptr<BulletConfig> config;
//	std::shared_ptr<Bullet> bullet;
//	std::weak_ptr<Bullet> bulletPtr;
//	ICollidable::ColliderTag colliderTag = SetBulletColliderTag(isPlayerShot);
//
//	bullet = Bullet::Create();
//	bulletPtr = bullet;
//
//	if (shotMode == ShotMode::SingleShot) {
//		config = std::make_unique<BulletConfig>(bulletType, 50, 50, Dir::Right, colliderTag);
//	}
//	else if (shotMode == ShotMode::TripleShot) {
//		config = std::make_unique<BulletConfig>(bulletType, 50, 50, Dir::Right, colliderTag);
//	}
//	bullet->Init(config.get());
//
//	if (bullet->GetSharedPtr() != nullptr)
//		return bullet->GetSharedPtr();
//	//
//}

ICollidable::ColliderTag EntityFactory::SetBulletColliderTag(SpaceShipModel shipModel)
{
	if (shipModel == SpaceShipModel::player)
		return ICollidable::ColliderTag::Tag_PlayerBullet;
	else
		return ICollidable::ColliderTag::Tag_EnemyBullet;
}


#pragma once
#include <memory>
#include "ICollidable.h"
#include "SpaceShip.h"

enum BulletType;
enum Dir;
class IGameEntity;

enum class SpaceShipModel {
	player = 1 << 0,
	fatty = 1 << 1,
	medium = 1 << 2,
	tiny = 1 << 3
};

enum class ShotMode {
	SingleShot,
	TripleShot,
	GodMode
};

class EntityFactory
{
private:
	static inline std::unique_ptr<EntityFactory> instance;

public:
	EntityFactory() = default;
	~EntityFactory() = default;
	EntityFactory(const EntityFactory&) = delete;
	EntityFactory(EntityFactory&&) = delete;
	EntityFactory& operator=(const EntityFactory&) = delete;

	static void Init();
	static std::shared_ptr<IGameEntity> CreateSpaceShip(SpaceShipModel spaceType);
	static std::shared_ptr<IGameEntity> CreateBullet(std::shared_ptr<SpaceShip> ship, Dir dir);//ShotMode shotMode, BulletType bulletType, bool isPlayerShot);
	static ICollidable::ColliderTag SetBulletColliderTag(SpaceShipModel shipModel);
};




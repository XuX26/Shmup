#pragma once

class ICollidable
{
public:
	ICollidable() = default;
	virtual ~ICollidable() = default;
	ICollidable(const ICollidable&) = delete;
	ICollidable(ICollidable&&) = delete;
	ICollidable& operator=(const ICollidable&) = delete;

	virtual int GetCollisionTag() const = 0;
	virtual int GetRadius() const = 0;
	virtual int GetPositionX() const = 0;
	virtual int GetPositionY() const = 0;

	enum ColliderTag
	{
		Tag_Player = 1,
		Tag_Enemy = 2,
		Tag_PlayerBullet = 4,
		Tag_EnemyBullet = 8,
	};
};

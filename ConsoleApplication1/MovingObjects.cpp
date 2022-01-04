#include "IMovingObjects.h"
#include "EntityFactory.h"
#include "Game.h"

void PlayerShip::Move(std::shared_ptr<SpaceShip> ship, int deltaTime)
{
	SDL_PumpEvents();
	if (state[SDL_SCANCODE_D])
		ship->posX += deltaTime * ship->speed / 100;
	else if(state[SDL_SCANCODE_A])
		ship->posX -= deltaTime * ship->speed / 100;
	if (state[SDL_SCANCODE_W])
		ship->posY -= deltaTime * ship->speed / 100;
	else if (state[SDL_SCANCODE_S])
		ship->posY += deltaTime * ship->speed / 100;
}

void PlayerShip::Fire(std::shared_ptr<SpaceShip> ship)
{
	SDL_PumpEvents();
	if (state[SDL_SCANCODE_SPACE])
	{
		if (ship->shotMode == ShotMode::SingleShot)
			Game::GetInstance()->AddEntity(EntityFactory::CreateBullet(ship, Dir::Right));
		else if (ship->shotMode == ShotMode::TripleShot) {
			Game::GetInstance()->AddEntity(EntityFactory::CreateBullet(ship, Dir::RightTop));
			Game::GetInstance()->AddEntity(EntityFactory::CreateBullet(ship, Dir::Right));
			Game::GetInstance()->AddEntity(EntityFactory::CreateBullet(ship, Dir::RightBot));
		}
	}
}

void EnemyShip::Move(std::shared_ptr<SpaceShip> ship, int deltaTime)
{
	ship->posX -= deltaTime * ship->speed / 100;
}

void EnemyShip::Fire(std::shared_ptr<SpaceShip> ship)
{
	if (ship->shotMode == ShotMode::SingleShot)
		Game::GetInstance()->AddEntity(EntityFactory::CreateBullet(ship, Dir::Left));
	else if (ship->shotMode == ShotMode::TripleShot) {
		Game::GetInstance()->AddEntity(EntityFactory::CreateBullet(ship, Dir::LeftTop));
		Game::GetInstance()->AddEntity(EntityFactory::CreateBullet(ship, Dir::Left));
		Game::GetInstance()->AddEntity(EntityFactory::CreateBullet(ship, Dir::LeftBot));
	}
}

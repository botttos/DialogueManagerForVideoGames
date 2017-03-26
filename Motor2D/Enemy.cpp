#include "j1App.h"
#include "Enemy.h"
#include "j1GameLayer.h"
#include "p2Log.h"
#include "j1Pathfinding.h"
#include "j1CollisionManager.h"
#include <math.h>

bool Enemy::Update(float dt)
{
	SearchForPlayer(speed, dt);

	return true;
}

bool Enemy::SearchForPlayer(int speed, float dt)
{
	//TODO clean this
	iPoint immediateDest;

	//Create path if player changes tile


	if (path.size() != 0)
	{
		
		
		if (immediateDest.x > currentPos.x)
			currentPos.x += SDL_ceil(speed * dt);
		else if (immediateDest.x < currentPos.x)
			currentPos.x -= SDL_ceil(speed * dt);

		if (immediateDest.y > currentPos.y)
			currentPos.y += SDL_ceil(speed * dt);
		else if (immediateDest.y < currentPos.y)
			currentPos.y -= SDL_ceil(speed * dt);

		//TODO: change iPoint pos to fPoint pos
		if (abs(immediateDest.x-currentPos.x) < 2 && abs(immediateDest.y - currentPos.y) < 2)
		{
			path.erase(path.begin());
		}
	}
	return false;
}

void Enemy::OnDeath()
{
	toDelete = true;
	col->to_delete = true;
}

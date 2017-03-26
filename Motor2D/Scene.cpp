#include "Scene.h"
#include "j1App.h"
#include "j1GameLayer.h"
#include <list>

bool Scene::Load(std::string data)
{
	return true;
}

Room::Room() : Scene() {}

bool Room::Load(std::string data)
{
	bool ret = true;

	return ret;
}

bool Room::CleanUp()
{
	return true;
}
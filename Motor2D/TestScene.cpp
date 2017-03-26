#include "TestScene.h"
#include "Scene.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1SceneManager.h"
#include "j1Input.h"
#include "j1PathFinding.h"
#include "j1Render.h"

TestScene::TestScene() : Scene("Test Scene"), testRoom(NULL) {}

bool TestScene::Load(std::string _data)
{
	bool ret = true;


	return ret;
}

// Called each loop iteration
bool TestScene::Update(float dt)
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
	{
		if (testRoom == NULL)
		{
			testRoom = new Room("tmpRoom");
			testRoom->Load("data");
		}
		else
		{
			testRoom->CleanUp();
			RELEASE(testRoom);
			testRoom = NULL;
		}
	}
	else
	{
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
			ret = false;
	}
	

	return ret;
}

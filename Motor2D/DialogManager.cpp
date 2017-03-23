#include "DialogManager.h"
#include "j1Input.h"
#include "j1Render.h"


DialogManager::DialogManager() : j1Module()
{
	name = ("dialogue");
}

bool DialogManager::Awake(pugi::xml_node & config)
{
	bool ret = true;

	LOG("Loading DialogManager data");
	folder = config.child("dialogues").attribute("folder").as_string();
	path = config.child("dialogues").first_child().attribute("file").as_string();

	std::string tmp = folder + path;

	char* buf;
	int size = App->fs->Load(tmp.c_str(), &buf);
	pugi::xml_parse_result result = dialogDataFile.load_buffer(buf, size);

	RELEASE(buf);

	if (result == NULL)
	{
		LOG("Could not load gui xml file %s. pugi error: %s", dialogDataFile, result.description());
		ret = false;
	}

	// Reseve dialogues memory
	/*for (pugi::xml_node npc = dialogNode.child("npc"); npc != NULL; npc = npc.next_sibling())
	{
		if (npc.attribute("id").as_int() == id) //If we found our NPC
		{
			uint dialogState = npc.attribute("state").as_uint(); //Dialog state of the NPC
			for (npc = npc.child("dialogue"); npc != NULL; npc = npc.next_sibling()) 
			{
				if (npc.attribute("state").as_uint() == dialogState)
				{

					std::string text = npc.child("text").attribute("value").as_string();
					if (npc.child("options").first_attribute().as_int() == 1)
					{
						//Choose action with UI method. TODO
						int action = 1;
						for(npc = npc.child("options").child("option"); npc != NULL; npc = npc.next_sibling("option"))
						{
							int test = npc.attribute("action").as_int();
							if (npc.attribute("action").as_int() == action)
							{
								std::string act = npc.attribute("value").as_string();
							}
						}
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}
	}*/

	return ret;
} 

bool DialogManager::Start()
{
	bool ret = true;
	dialogNode = dialogDataFile.child("npcs");
	return ret;
}

bool DialogManager::Update(float dt)
{
	//Only for test. Send the npc ID to Dialog method
	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
		DialogCharge(2);

	return true;
}

bool DialogManager::DialogCharge(const int id)
{	
	//Iterate all NPCs
	for (pugi::xml_node npc = dialogNode.child("npc"); npc != NULL; npc = npc.next_sibling())
	{
		if (npc.attribute("id").as_int() == id) //If we found our NPC
		{
			uint dialogState = npc.attribute("state").as_uint(); //Dialog state of the NPC
			for (npc = npc.child("dialogue"); npc != NULL; npc = npc.next_sibling()) 
			{
				if (npc.attribute("state").as_uint() == dialogState)
				{

					std::string text = npc.child("text").attribute("value").as_string();
					if (npc.child("options").first_attribute().as_int() == 1)
					{
						//Choose action with UI method. TODO
						int action = 1;
						for(npc = npc.child("options").child("option"); npc != NULL; npc = npc.next_sibling("option"))
						{
							int test = npc.attribute("action").as_int();
							if (npc.attribute("action").as_int() == action)
							{
								std::string act = npc.attribute("value").as_string();
							}
						}
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}
	}
	return false;
}

Dialog::Dialog(int id, int state): id(id), state(state)
{}

Dialog::~Dialog()
{}

Line::Line(bool interaction, std::string text) : interaction(interaction)
{
	line = new std::string(text);
}

Line::Line(bool interaction, std::string option1, std::string option2) : interaction(interaction)
{
	options.push_back(&option1);
	options.push_back(&option1);
}


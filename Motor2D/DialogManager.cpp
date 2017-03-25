#include "DialogManager.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Gui.h"

DialogManager::DialogManager() : j1Module()
{
	name = ("dialogue");
}

DialogManager::~DialogManager()
{
	dialog.clear();
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
	

	return ret;
} 

bool DialogManager::Start()
{
	bool ret = true;
	dialogNode = dialogDataFile.child("npcs");
	// Allocate memory to dialog
	int i = 0;
	for (pugi::xml_node npc = dialogNode.child("npc"); npc != NULL; npc = npc.next_sibling(), i++)
	{
		//Allocate Dialog ID and his State
		Dialog* tmp = new Dialog(npc.attribute("id").as_int(), npc.attribute("state").as_uint());
		dialog.push_back(tmp);

		//Allocate texts, options and responses
		for (pugi::xml_node dialogue = npc.child("dialogue"); dialogue != NULL; dialogue = dialogue.next_sibling())
		{
			for (pugi::xml_node text = dialogue.child("text"); text != NULL; text = text.next_sibling("text"))
			{
				Line* tmp = new Line(false, dialogue.attribute("state").as_int(), text.attribute("value").as_string());
				dialog[i]->texts.push_back(tmp);
			}
			for (pugi::xml_node option = dialogue.child("options").child("option"); option != NULL; option = option.next_sibling())
			{
				Line* tmp = new Line(true, dialogue.attribute("state").as_int(), option.attribute("value").as_string());
				dialog[i]->texts.push_back(tmp);
			}
			for (pugi::xml_node response = dialogue.child("response"); response != NULL; response = response.next_sibling())
			{
				Line* tmp = new Line(false, dialogue.attribute("state").as_int(), response.attribute("value").as_string());
				dialog[i]->texts.push_back(tmp);
			}
		}
	}

	//Prepare UI to print
	screen = App->gui->CreateScreen(screen);
	text_on_screen = (UI_String*)App->gui->Add_element(STRING, this);
	text_on_screen->Set_Active_state(false);
	text_on_screen->Set_Interactive_Box({0, 0, 0, 0});
	screen->AddChild(text_on_screen);

	text_on_screen_Options = (UI_String*)App->gui->Add_element(STRING, this);
	text_on_screen_Options->Set_Active_state(false);
	text_on_screen_Options->Set_Interactive_Box({ 0, 40, 0, 0 });
	screen->AddChild(text_on_screen_Options);
	text_on_screen->Set_Active_state(true);
	text_on_screen_Options->Set_Active_state(false);
	return ret;
}

bool DialogManager::Update(float dt)
{
	
	return true;
}

bool DialogManager::PostUpdate()
{
	/*--- CODE TO TEST RESULTS IN-GAME ---*/
	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		if (id == 1)
		{
			id = 2;
		}
		else
		{
			id = 1;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
	{
		if (state == 0)
		{
			state = 1;
		}
		else
		{
			state = 0;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		text_on_screen->Set_Interactive_Box({ 0, 40, 0, 0 });
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{

	}
	/*--- END ---*/

	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
	{
		dialogState++;
	}

	SelectDialogue(id, state);
	return true;
}

bool DialogManager::SelectDialogue(int id, int state)
{
	bool ret = false;
	//Search the correct ID
	for (int i = 0; i < dialog.size(); i++)
	{
		if (dialog[i]->id == id)
		{
			if (dialogState >= dialog[i]->texts.size()-1)
			{
				dialogState = 0;
			}
			for (int j = 0; (j+dialogState) < dialog[i]->texts.size(); j++) //Search correct dialog
			{
				
				if (dialog[i]->texts[j+dialogState]->NPCstate == state)
				{
					if (dialog[i]->texts[j+dialogState]->interaction == false)
					{
						text_on_screen_Options->Set_Active_state(false); //Unable second option
						
						text_on_screen->Set_String((char*)dialog[i]->texts[j+dialogState]->line->c_str());
						return true;
					}
					else if (dialog[i]->texts[j+dialogState]->interaction == true) //Player chooses the option
					{
						text_on_screen_Options->Set_Active_state(true); //Enable second option
						text_on_screen_Options->Set_String((char*)dialog[i]->texts[j + dialogState]->line->c_str());

						text_on_screen->Set_String((char*)dialog[i]->texts[j+dialogState]->line->c_str());
						return true;
					}
				}
			}
		}
	}

	return ret;
}

Dialog::Dialog(int id, int state): id(id), state(state)
{}

Dialog::~Dialog()
{
	texts.clear();
}

Line::Line(bool interaction, int NPCstate, std::string text) : interaction(interaction), NPCstate(NPCstate)
{
	line = new std::string(text);
}

Line::~Line()
{}


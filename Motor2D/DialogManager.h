#ifndef __DIALOG_MANAGER_H__
#define __DIALOG_MANAGER_H__


#include "PugiXml\src\pugixml.hpp"
#include <list>
#include <map>
#include <string>
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1FileSystem.h"
#include "j1GameLayer.h"
#include "j1App.h"
#include "UI_String.h"

class Entity;
class Player;
class Enemy;
class UI_element;
class UI_String;
enum ENTITY_TYPE;
enum ENEMY_TYPE;

class Line
{
public:

	Line(bool interaction,int NPCstate, std::string text);
	~Line();

	bool interaction;
	int NPCstate;
	std::string* line = nullptr;
};

class Dialog
{
private:
public:

	Dialog(int id, int state);
	Dialog();
	~Dialog();

	int id;
	int state;
	std::vector<Line*> texts;
};

class DialogManager : public j1Module
{
public:

	DialogManager();
	bool Awake(pugi::xml_node& config);
	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool SelectDialogue(int id, int state);

public:
	std::string folder;
	std::string path;
	pugi::xml_document dialogDataFile;
	pugi::xml_node dialogNode;

	int dialogState = 0;

	UI_element* screen = nullptr;
	UI_String* text_on_screen = nullptr;
	UI_String* text_on_screen_Options = nullptr;
	std::vector<Dialog*> dialog;

/*----------CODE TO TEST RESULTS IN-GAME --------------*/
	int id = 1;
	int state = 0;
};

#endif
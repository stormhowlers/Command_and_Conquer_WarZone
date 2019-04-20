#ifndef __Player_H__
#define __Player_H__

#include "Module.h"
#include "Troop.h"
#include "Building.h"
#include "Entity.h"
#include "Troop.h"
#include "SDL\include\SDL_gamecontroller.h"

struct SDL_Texture;
struct GamePad
{
	SDL_GameController* GameController = nullptr;
	SDL_Joystick* joy = nullptr;

	bool Connected = false;
	bool State[MAX_BUTTONS];

	j1KeyState Controller[MAX_BUTTONS]; //This is the one you check. EXAMPLE: App->input->name.Controller[JOY_RIGHT] == KEY_REPEAT 

	int LeftAxisX = 0;
	int LeftAxisY = 0;

};

struct GeneralUI
{
	bool upgrade, repair;
	string name;
	uint level, health, unique;
};

class Player : public Module
{
public:
	enum CURRENT_UI
	{
		NONE,
		CURR_MAIN_MENU,
		CURR_MAIN,
		CURR_BUILD,
		CURR_DEPLOY,
		CURR_CAST,
		CURR_GENERAL,
		CURR_CREATE_TROOPS,
		CURR_PAUSE,
		CURR_PAUSE_SETTINGS,
		CURR_PAUSE_ABORT,
		CURR_WIN_SCREEN,
		ENDGAME
	};

	Player();
	~Player();

	bool Start();
	//bool Awake(pugi::xml_node &config);
	bool Update(float dt);
	void SpawnEntity();
	bool PostUpdate();
	bool CleanUp();

	void GetCurrentTile(int& x, int& y);

	// ---------------------- UI functions -----------------------------------------

	void UpdateVisibility(); //update gui visibility
	void DoLogic(UI_Element* data); //gui actions
	void UpdateFocus(uint data);	//updates where the focus is pointing
	void GotoPrevWindows(uint data);
	UI_Element* GetUI_Element(uint data); //returns the window we are currently on
	void Update_troop_image(int type);

	// -----------------------------------------------------------------------------

	void CreateTroop(int type, int number);

	bool CheckBuildingPos();
	Collider GetCollider(pair<int, int> dimensions, pair<int,int> topTile_pos);
	void UpdateWalkabilityMap(bool isWalkable, Collider collider);
	bool DeleteEntity(Entity* entity);
	
public:
	bool onUI = false;
	bool isBuilding = false;
	bool isDeploying = false;
	bool isCasting = false;
	bool isPaused = false;

	Collider collider;
	pair<int, int> offset;
	Entity::entityType type;

	Entity* Townhall = nullptr;

	bool isPlayer1 = false;
	string team;

	uint gold = 0;
	uint time_iterator = 0;

	uint last_currentUI = 0;
	uint currentUI = 0;
	int actual_capacity = 0;
  
	//bool entityAdded;
	//Entity* previewEntity;

	vector<SDL_Rect> preview_rects;

	SDL_Rect LiveBar;
	int health, max_health;

	// Live of TOWN HALL
	int live = 0;
	
	//index for testing previews
	int curr = 1;

	GamePad gamepad;

	pair<int,int> currentTile;
	pair<int, int> x_limits_player1, y_limits_player1;
	pair<int, int> x_limits_player2, y_limits_player2;

	list<Building*> buildings;
	list<Troop*> troops;

	int SoldiersCreated = 0;
	int TankmansCreated = 0;
	int InfiltratorsCreated = 0;
	int EngineersCreated = 0;
	int WarHoundsCreated = 0;

	//---
	list<UI_Element*> UI_elements;

	list<UI_Element*>::iterator focus;
	list<UI_Element*>::iterator last_element;

	// --- UI --- //
	
	UI_Element* Gold_UI = nullptr;

	UI_Element* Y_to_Main = nullptr;
	UI_Element* Y_to_Main2 = nullptr;
	UI_Element* RB_img = nullptr;
	UI_Element* LB_img = nullptr;
	bool Y_pressed = false;

	UI_Element* Main_UI = nullptr;
	UI_Element* Build_icon = nullptr;
	UI_Element* Deploy_icon = nullptr;
	UI_Element* Cast_icon = nullptr;

	UI_Element* Build_UI = nullptr;
	UI_Element* Def_AOE_icon = nullptr;
	UI_Element* Def_Target_icon = nullptr;
	UI_Element* Mines_icon = nullptr;
	UI_Element* Barracks_icon = nullptr;

	UI_Element* Deploy_UI = nullptr;
	UI_Element* Soldier_icon = nullptr;
	UI_Element* Soldier_text = nullptr;
	char soldier_label[4] = "0";
	UI_Element* Tankman_icon = nullptr;
	UI_Element* Tankman_text = nullptr;
	char tankman_label[4] = "0";
	UI_Element* Infiltrator_icon = nullptr;
	UI_Element* Infiltrator_text = nullptr;
	char infiltrator_label[4] = "0";
	UI_Element* Engineer_icon = nullptr;
	UI_Element* Engineer_text = nullptr;
	char engineer_label[4] = "0";
	UI_Element* War_hound_icon = nullptr;
	UI_Element* War_hound_text = nullptr;
	char war_hound_label[4] = "0";

	UI_Element* Cast_UI = nullptr;
	UI_Element* Missiles_icon = nullptr;
	UI_Element* Cast2_icon = nullptr;
	UI_Element* Cast3_icon = nullptr;

	// Selected Building UI
	UI_Element* General_UI = nullptr;
	UI_Element* Upgrade_icon = nullptr;
	UI_Element* Repair_icon = nullptr;
	UI_Element* UpgradeCost_text = nullptr;
	char upgrade_cost_label[10] = " - 0000 $";
	UI_Element* RepairCost_text = nullptr;
	char repair_cost_label[10] = " - 0000 $";
	UI_Element* Name_text = nullptr;
	char name_label[10] = "Name:  ";
	UI_Element* Level_text = nullptr;
	char level_label[10] = "Lvl:  ";
	UI_Element* Health_text = nullptr;
	char health_label[10] = "HP:  ";
	UI_Element* Damage_text = nullptr; //only for defense buildings
	UI_Element* Prod_text = nullptr; //only for townhall & mines
	UI_Element* Capacity_text = nullptr; //only for barracks

	// Create troops UI --------------------------
	UI_Element* Create_Troops_UI = nullptr;
	UI_Element* left_img = nullptr;
	UI_Element* troop_icon = nullptr;
	UI_Element* right_img= nullptr;
	UI_Element* plus = nullptr;
	UI_Element* minus = nullptr;
	UI_Element* accept_button = nullptr;
	UI_Element* cancel_button = nullptr;

	int UI_troop_type = 9; //select type of troop (9 is soldier) 
	int number_of_troops = 0;

	UI_Element* num_troops_text = nullptr;
	char num_troops_label[4] = "0";

	// ---------------------------------------------

	// Pause Menu
	UI_Element* Pause_UI = nullptr;

	UI_Element* Resume_Button = nullptr;
	UI_Element* Resume_text = nullptr;
	char resume_label[12] = "Resume Game";

	UI_Element* Settings_Button = nullptr;
	UI_Element* Settings_text = nullptr;
	char settings_label[9] = "Settings";

	UI_Element* Abort_Button = nullptr;
	UI_Element* Abort_text = nullptr;
	char abort_label[14] = "Abort Mission";

	// Pause Settings Menu
	UI_Element* Settings_UI = nullptr;

	UI_Element* Music_Settings = nullptr;
	UI_Element* Music_text = nullptr;
	char Music_label[14] = "Music Volume";
	UI_Element* Music_Slider = nullptr;
	UI_Element* Music_Slider_text = nullptr;
	char Music_Slider_label[5] = "0";
	UI_Element* Music_Slider_Button = nullptr;

	UI_Element* FX_Settings = nullptr;
	UI_Element* FX_text = nullptr;
	char FX_label[10] = "FX Volume";
	UI_Element* FX_Slider = nullptr;
	UI_Element* FX_Slider_text = nullptr;
	char FX_Slider_label[5] = "0";
	UI_Element* FX_Slider_Button = nullptr;

	// Pause Abort Mission

	UI_Element* Abort_UI = nullptr;
	UI_Element* Abort_Message = nullptr;
	char Abort_message_label[27] = "What would you like to do?";

	UI_Element* Quit = nullptr;
	UI_Element* Quit_text = nullptr;
	char Quit_label[10] = "Surrender";

	UI_Element* Restart = nullptr;
	UI_Element* Restart_text = nullptr;
	char Restart_label[13] = "Restart Game";
	
	UI_Element* win_screen = nullptr;
};

#endif // !__Player_H__
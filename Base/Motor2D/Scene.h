#ifndef __Scene_H__
#define __Scene_H__

#include "Module.h"
#include "UI_Element.h"

struct SDL_Texture;

enum DEPLOY
{
	DEPLOY_SOLDIER = 1,
	DEPLOY_TANKMAN,
	DEPLOY_INFILTRATOR,
	DEPLOY_ENGINEER,
	DEPLOY_WAR_HOUND
};

enum CAST
{
	CAST_MISSILES = 1,
	CAST_2,
	CAST_3
};


class Scene : public Module
{
public:
	Scene();
	virtual ~Scene();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	bool Load(pugi::xml_node& data);
	bool Save(pugi::xml_node& data) const;

	bool Load_level(int map);
	void SpawnEnemies();
	void SpawnEntities();

public:
	vector<string*> map_names;
	float fade_time;

	uint currentMap;
	uchar* Wmap;

	bool pause;
	bool godmode;
	bool to_end;
	bool change;

	string current_track;
	string current_fx;

private:
	SDL_Texture* debug_tex;
	SDL_Texture* cursor_tex;
};

#endif // __Scene_H__

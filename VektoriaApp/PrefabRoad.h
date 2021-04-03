#pragma once
#include "Vektoria\Root.h"
#include <string.h>

using namespace Vektoria;

class PrefabRoad
{
public:

	PrefabRoad(char *tmp_modelpath, char* tmp_groundhitboxpath, char* tmp_frontalhitboxpath, CGeos *tmp_roadTilesHitboxGround, CGeos *tmp_roadTilesHitboxFrontal, CHVector tmp_itemspawn1, CHVector tmp_itemspawn2, CHVector tmp_itemspawn3);
	~PrefabRoad(void);

	void addtoScene(CPlacement *tmp_roadPlacement, CPlacement* tmp_hitboxPlacement, CPlacement* tmp_hitboxFrontalPlacement);
	void subfromScene(CPlacement *tmp_roadPlacement, CPlacement* tmp_hitboxPlacement, CPlacement* tmp_hitboxFrontalPlacement);
	CHVector getItemspawnPosition();

private:

	char modelpath[_MAX_PATH];
	char groundhitboxpath[_MAX_PATH];
	char frontalhitboxpath[_MAX_PATH];

	// Positionen f�r m�gliche Itemspawns
	CHVector itemspawns[3];

	CGeo* roadModel;
	CGeo* roadHitboxGround;
	CGeo* roadHitboxFrontal;
	CFileWavefront loadModel;
	CFileWavefront loadHitboxGround;
	CFileWavefront loadHitboxFrontal;
};


#pragma once
#include "Vektoria\Root.h"
#include <string.h>

using namespace Vektoria;

class PrefabRoad
{
public:

	PrefabRoad(char *tmp_modelpath, char* tmp_hitboxpath, CGeos *tmp_roadTilesHitbox, CHVector tmp_itemspawn1, CHVector tmp_itemspawn2, CHVector tmp_itemspawn3);
	~PrefabRoad(void);

	void addtoScene(CPlacement *tmp_roadPlacement, CPlacement* tmp_hitboxPlacement);
	void subfromScene(CPlacement *tmp_roadPlacement, CPlacement* tmp_hitboxPlacement);
	CHVector getItemspawnPosition();

private:

	char modelpath[_MAX_PATH];
	char hitboxpath[_MAX_PATH];

	// Positionen für mögliche Itemspawns
	CHVector itemspawns[3];

	CGeo* roadModel;
	CGeo* roadHitbox;
	CFileWavefront loadModel;
	CFileWavefront loadHitbox;
};


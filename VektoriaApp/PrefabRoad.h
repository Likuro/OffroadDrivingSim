#pragma once
#include "Vektoria\Root.h"
#include <string.h>

using namespace Vektoria;

class PrefabRoad
{
public:

	PrefabRoad(char *tmp_modelpath, char* tmp_hitboxpath, CGeos *tmp_roadTilesHitbox);
	~PrefabRoad(void);

	void addtoScene(CPlacement *tmp_roadPlacement, CPlacement* tmp_hitboxPlacement);
	void subfromScene(CPlacement *tmp_roadPlacement, CPlacement* tmp_hitboxPlacement);

private:

	char modelpath[_MAX_PATH];
	char hitboxpath[_MAX_PATH];

	CGeo* roadModel;
	CGeo* roadHitbox;
	CFileWavefront loadModel;
	CFileWavefront loadHitbox;
};


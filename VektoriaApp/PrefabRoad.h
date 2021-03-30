#pragma once
#include "Vektoria\Root.h"
#include <string.h>

using namespace Vektoria;

class PrefabRoad
{
public:

	PrefabRoad(char *tmp_path);
	~PrefabRoad(void);

	void addtoScene(CPlacement *tmp_roadPlacement);
	void subfromScene(CPlacement *tmp_roadPlacement);

private:

	char path[_MAX_PATH];

	CGeo* RoadModel;
	CFileWavefront LoadModel;
};


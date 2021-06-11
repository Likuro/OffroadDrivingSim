#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;


class PrefabTerrain
{
public:
	PrefabTerrain(int tmp_roadTilelength, int tmp_roadTilewidth, int tmp_roadTileheight, int tmp_RoadTileBoundingBox);
	~PrefabTerrain();

	CGeoTerrain* getTerrain();

private:
	CGeoTerrain myTerrain;
	CMaterial myTerrainMaterial;
};


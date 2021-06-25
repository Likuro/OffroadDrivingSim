#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;


class PrefabTerrain
{
public:
	PrefabTerrain(int tmp_roadTilelength, int tmp_roadTilewidth, int tmp_roadTileheight, int tmp_RoadTileBoundingBox);
	~PrefabTerrain();

	CGeoTerrain* getTerrain();
	void initTerrain(CPerlin* tmp_perlinNoise, CMaterial* tmp_material);

private:
	CGeoTerrain myTerrain;

	//RoadSettingsSpeicher
	int my_roadTilelength;
	int my_roadTilewidth;
	int my_roadTileheight;
	int my_RoadTileBoundingBox;
	CBlob* my_blob;
};

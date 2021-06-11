#include "PrefabTerrain.h"

PrefabTerrain::PrefabTerrain(int tmp_roadTilelength, int tmp_roadTilewidth, int tmp_roadTileheight, int tmp_RoadTileBoundingBox)
{
	myTerrainMaterial.MakeTextureDiffuse("textures\\PrototypeTextures\\Green\\texture_06.png");
	myTerrain.InitQuick(tmp_roadTilelength * 3, tmp_roadTilewidth * 3, (tmp_roadTileheight * tmp_RoadTileBoundingBox), false, &myTerrainMaterial, 100, 100, 0, 0, 10, 10);
}

PrefabTerrain::~PrefabTerrain()
{
}

CGeoTerrain* PrefabTerrain::getTerrain()
{
	return &myTerrain;
}

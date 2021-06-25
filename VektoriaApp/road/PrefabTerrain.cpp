#include "PrefabTerrain.h"

PrefabTerrain::PrefabTerrain(int tmp_roadTilelength, int tmp_roadTilewidth, int tmp_roadTileheight, int tmp_RoadTileBoundingBox)
{
	my_roadTilelength = tmp_roadTilelength;
	my_roadTilewidth = tmp_roadTilewidth;
	my_roadTileheight = tmp_roadTileheight;
	my_RoadTileBoundingBox = tmp_RoadTileBoundingBox;
}

PrefabTerrain::~PrefabTerrain()
{
}

CGeoTerrain* PrefabTerrain::getTerrain()
{
	return &myTerrain;
}

void PrefabTerrain::initTerrain(CPerlin* tmp_perlinNoise, CMaterial* tmp_material)
{
	//myTerrain.InitQuick(my_roadTilelength * 3, my_roadTilewidth * 3, (my_roadTileheight * my_RoadTileBoundingBox) * 10.f, true, &myTerrainMaterial, 100, 100, 0, 0, 10, 10);
	my_blob = new CBlob(0.5f, 0.5f, 0.5f, 0.5f, (my_roadTileheight * my_RoadTileBoundingBox) * 50.f, eBlobShapeGround_Radial, eBlobShapeSide_Hill, tmp_perlinNoise);
	myTerrain.AddBlob(my_blob);
	myTerrain.CreateField(my_roadTilelength * 5.f, my_roadTilewidth * 9.f, 200, 200);
	myTerrain.InitFromOther(myTerrain, tmp_material);
}

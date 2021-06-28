#include "RoadTile.h"



RoadTile::RoadTile(PrefabRoad* tmp_myPrefabRoad, CPlacement* tmp_DrivingScenePlacement, int tmp_roadTilewidth, int tmp_roadTilelength, int tmp_roadTileheight, int tmp_RoadTileBoundingBox, CGeoTerrains* tmp_roadTilesGravityPlanes, CGeoQuad* tmp_groundplane)
{
	this->myDrivingScenePlacement = tmp_DrivingScenePlacement;
	this->myPrefabRoad = tmp_myPrefabRoad;
	this->myDrivingScenePlacement->AddPlacement(&myBasePlacement);

	myTerrainPointerL = nullptr;
	myTerrainPointerR = nullptr;

	myBasePlacement.AddPlacement(&myRoadPlacement);
	myRoadPlacement.AddPlacement(&myItemSpawn);
	myRoadPlacement.AddPlacement(&myHitboxGroundPlacement);
	myRoadPlacement.AddPlacement(&myHitboxFrontalPlacement);
	myBasePlacement.AddPlacement(&myTerrainPlacementL);
	myBasePlacement.AddPlacement(&myTerrainPlacementR);
	myRoadPlacement.AddPlacement(&myGravityPlacement);
	myBasePlacement.AddPlacement(&myGroundPlacement);

	myTerrainPlacementL.TranslateZ(-((float)tmp_roadTilewidth*5 +((float)tmp_roadTilewidth *((float)tmp_RoadTileBoundingBox/2))));
	myTerrainPlacementL.TranslateYDelta(-(tmp_roadTileheight * (2 + tmp_RoadTileBoundingBox / 2)));
	myTerrainPlacementL.RotateYDelta(-HALFPI);

	myTerrainPlacementR.TranslateZ(((float)tmp_roadTilewidth*5 + ((float)tmp_roadTilewidth * ((float)tmp_RoadTileBoundingBox / 2))));
	myTerrainPlacementR.TranslateYDelta(-(tmp_roadTileheight * (2 + tmp_RoadTileBoundingBox / 2)));
	myTerrainPlacementR.RotateYDelta(-HALFPI);

	myGravityPlacement.TranslateY(-100);
	GravityMaterial.MakeTextureDiffuse("textures\\PrototypeTextures\\Green\\texture_06.png");
	myGravityPlacement.AddGeo(&GravityPlane);
	GravityPlane.InitQuick(tmp_roadTilelength, tmp_roadTilewidth*3, 10, false, &GravityMaterial, 4, 4, 0, 0, 10, 10);
	tmp_roadTilesGravityPlanes->Add(&GravityPlane);

	myGroundPlacement.AddGeo(tmp_groundplane);
	myGroundPlacement.TranslateZ(-(tmp_roadTileheight*(2+tmp_RoadTileBoundingBox/2)));
	myGroundPlacement.RotateXDelta(-HALFPI);

	this->myHitboxGroundPlacement.SetDrawingOff();
	this->myHitboxFrontalPlacement.SetDrawingOff();
}

RoadTile::~RoadTile(void)
{
}

void RoadTile::addToScene(PrefabRoad* tmp_myPrefabRoad)
{
	this->myPrefabRoad = tmp_myPrefabRoad;
	this->myPrefabRoad->addtoScene(&myRoadPlacement, &myHitboxGroundPlacement, &myHitboxFrontalPlacement);
	myItemSpawnVector = myPrefabRoad->getItemspawnPosition();
	this->myItemSpawn.Translate(myItemSpawnVector);
}

void RoadTile::removefromScene()
{
	this->myPrefabRoad->subfromScene(&myRoadPlacement, &myHitboxGroundPlacement, &myHitboxFrontalPlacement);
	removeTerrain();
	removeItem();
}

void RoadTile::move(float tmp_lane, float tmp_slope, float tmp_moveZ)
{
	myBasePlacement.TranslateZDelta(tmp_moveZ);
	myRoadPlacement.TranslateX(tmp_lane);
	myRoadPlacement.TranslateYDelta(tmp_slope);
}

float RoadTile::getZPos()
{
	return myBasePlacement.GetPos().GetZ();
}

void RoadTile::addItem(CPlacement* tmp_itemPlacement)
{
	myItem = tmp_itemPlacement;
	myItemSpawn.AddPlacement(myItem);
}

void RoadTile::removeItem()
{
	if (myItem != nullptr) {
		this->myItemSpawn.SubPlacement(myItem);
		myItem = nullptr;
	}
}

void RoadTile::addTerrain(CGeoTerrain* tmp_terrain)
{
	myTerrainPointerL = tmp_terrain;
	myTerrainPointerR = tmp_terrain;

	myTerrainPlacementL.AddGeo(myTerrainPointerL);
	myTerrainPlacementR.AddGeo(myTerrainPointerR);
}

void RoadTile::removeTerrain()
{
	if (myTerrainPointerL != nullptr && myTerrainPointerR != nullptr)
	{
		myTerrainPlacementL.SubGeo(myTerrainPointerL);
		myTerrainPlacementR.SubGeo(myTerrainPointerR);

		myTerrainPointerL = nullptr;
		myTerrainPointerR = nullptr;
	}
}

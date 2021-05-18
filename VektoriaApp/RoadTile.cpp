#include "RoadTile.h"



RoadTile::RoadTile(PrefabRoad* tmp_myPrefabRoad, CPlacement* tmp_roadPlacement, int tmp_roadTilewidth, int tmp_roadTilelength, CGeoTerrains* tmp_roadTilesGravityPlanes)
{
	this->myRoadPlacement = tmp_roadPlacement;
	this->myPrefabRoad = tmp_myPrefabRoad;
	this->myRoadPlacement->AddPlacement(&myItemSpawn);
	this->myRoadPlacement->AddPlacement(&myHitboxGroundPlacement);
	this->myRoadPlacement->AddPlacement(&myHitboxFrontalPlacement);
	this->myRoadPlacement->AddPlacement(&myGravityPlacement);
	myGravityPlacement.TranslateY(-100);
	GravityMaterial.MakeTextureDiffuse("textures\\PrototypeTextures\\Green\\texture_06.png");
	myGravityPlacement.AddGeo(&GravityPlane);
	GravityPlane.InitQuick(tmp_roadTilelength, tmp_roadTilewidth*3, 10, false, &GravityMaterial, 4, 4, 0, 0, 10, 10);

	tmp_roadTilesGravityPlanes->Add(&GravityPlane);
	this->myHitboxGroundPlacement.SetDrawingOff();
	this->myHitboxFrontalPlacement.SetDrawingOff();
}

RoadTile::~RoadTile(void)
{
}

void RoadTile::addToScene(PrefabRoad* tmp_myPrefabRoad)
{
	this->myPrefabRoad = tmp_myPrefabRoad;
	this->myPrefabRoad->addtoScene(myRoadPlacement, &myHitboxGroundPlacement, &myHitboxFrontalPlacement);
	myItemSpawnVector = myPrefabRoad->getItemspawnPosition();
	this->myItemSpawn.Translate(myItemSpawnVector);
}

void RoadTile::removefromScene()
{
	this->myPrefabRoad->subfromScene(myRoadPlacement, &myHitboxGroundPlacement, &myHitboxFrontalPlacement);
	removeItem();
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

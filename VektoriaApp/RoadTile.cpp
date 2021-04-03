#include "RoadTile.h"



RoadTile::RoadTile(PrefabRoad* tmp_myPrefabRoad, CPlacement* tmp_roadPlacement)
{
	this->myRoadPlacement = tmp_roadPlacement;
	this->myPrefabRoad = tmp_myPrefabRoad;
	this->myRoadPlacement->AddPlacement(&myItemSpawn);
	this->myRoadPlacement->AddPlacement(&myHitboxGroundPlacement);
	this->myRoadPlacement->AddPlacement(&myHitboxFrontalPlacement);
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
	this->myItemSpawn.SubPlacement(myItem);
}

void RoadTile::addItem(CPlacement* tmp_itemPlacement)
{
	myItem = tmp_itemPlacement;
	myItemSpawn.AddPlacement(myItem);
}

#include "RoadTile.h"



RoadTile::RoadTile(PrefabRoad* tmp_myPrefabRoad, CPlacement* tmp_roadPlacement)
{
	this->myRoadPlacement = tmp_roadPlacement;
	this->myPrefabRoad = tmp_myPrefabRoad;
	this->myRoadPlacement->AddPlacement(&myItemSpawn);
	this->myRoadPlacement->AddPlacement(&myHitboxPlacement);
	this->myHitboxPlacement.SetDrawingOff();
}

RoadTile::~RoadTile(void)
{
}

void RoadTile::addToScene(PrefabRoad* tmp_myPrefabRoad)
{
	this->myPrefabRoad = tmp_myPrefabRoad;
	this->myPrefabRoad->addtoScene(myRoadPlacement, &myHitboxPlacement);
	myItemSpawnVector = myPrefabRoad->getItemspawnPosition();
	this->myItemSpawn.Translate(myItemSpawnVector);
}

void RoadTile::removefromScene()
{
	this->myPrefabRoad->subfromScene(myRoadPlacement, &myHitboxPlacement);
}

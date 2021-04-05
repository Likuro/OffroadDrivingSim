#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;

// eAlignObjDir to align the camera with the direction of the obj, eAlignXAxisPositive and eAlignZAxisPositive are self-explanatory 
enum eAlign {eAlignObjDir, eAlignXAxisPositive, eAlignZAxisPositive};

class ThirdPersonCamera :   public CPlacement
{
public:
	void Init(float distance, float height, eAlign alignement, CPlacement* followObject, CCamera* camera);
	void update();


private:
	CCamera* m_Camera;
	CPlacement* m_FollowObject;
	CPlacement m_CameraSwivel;
	float m_distance;
	float m_height;
	eAlign m_alignement;
};


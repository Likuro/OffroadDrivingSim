#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;

// eAlignObjDir to align the camera with the direction of the obj, eAlignXAxisPositive and eAlignZAxisPositive are self-explanatory 
enum eAlign {eAlignObjDir, eAlignXAxisPositive, eAlignZAxisNegative};

class ThirdPersonCamera :   public CPlacement
{
public:
	void Init(float distance, float height, eAlign alignement, CPlacement* followObject, CCamera* camera);
	void update(float fTimeDelta);
	// Zoomt rein und raus um den Wert value (negativ für raus, positiv für rein)
	void zoom(float value);


private:
	CCamera* m_Camera;
	CPlacement* m_FollowObject;
	CPlacement m_CameraSwivel;
	CHVector m_dirCamera;
	float m_distance;
	float m_height;
	float m_stiffness = 5.f;
	float m_yaw;
	float m_oldYaw;
	float m_maxZoom = 0.1f;
	float m_zoom = 1.f;
	eAlign m_alignement;
};


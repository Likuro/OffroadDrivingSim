#include "ThirdPersonCamera.h"

void ThirdPersonCamera::Init(float distance, float height, eAlign alignement, CPlacement* followObject, CCamera* camera)
{
	m_distance = distance;
	m_height = height;
	m_alignement = alignement;
	m_FollowObject = followObject;
	m_Camera = camera;

	// Aufbau der Hierarchie
	this->AddPlacement(&m_CameraSwivel);
	m_CameraSwivel.AddCamera(m_Camera);

	this->update();
}

void ThirdPersonCamera::update()
{
	CHVector followPos = m_FollowObject->GetPos();
	float angle = asinf(m_height / m_distance);
	switch (m_alignement)
	{
	case eAlignObjDir:
		// not fully implemented
		this->GetMatGlobal().CopyRotationY(m_FollowObject->GetMatGlobal().GetYaw());
		break;
	case eAlignXAxisPositive:
		// not fully implemented
		this->Translate(followPos.x - (m_height / tan(angle)), followPos.y + m_height, followPos.z);
		break;
	case eAlignZAxisPositive:
		this->RotateY(HALFPI);
		this->TranslateDelta(followPos.x, followPos.y + m_height, followPos.z - (m_height / tan(angle)));
		m_CameraSwivel.RotateY(HALFPI);
		break;
	default:
		break;
	}
	m_CameraSwivel.RotateZDelta(angle);
}

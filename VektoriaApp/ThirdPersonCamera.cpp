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
	m_CameraSwivel.RotateX(-angle);
	float yaw = m_FollowObject->GetMat().GetYaw();
	CHMat mat;	
	mat.RotateY(yaw);
	mat.RotateXDelta(-0.03f);//added by Mohamed
	CHVector toCamera(0.f, m_height, (m_height / tan(angle)));
	toCamera = mat * toCamera;

	switch (m_alignement)
	{
	case eAlignObjDir:
		this->Translate(followPos + toCamera);
		m_CameraSwivel.RotateYDelta(yaw);
		break;
	case eAlignXAxisPositive:
		this->Translate(followPos.x - (m_height / tan(angle)), followPos.y + m_height, followPos.z);
		m_CameraSwivel.RotateYDelta(HALFPI + PI);
		break;
	case eAlignZAxisPositive:
		this->Translate(followPos.x, followPos.y + m_height, followPos.z - (m_height / tan(angle)));
		m_CameraSwivel.RotateYDelta(PI);
		break;
	default:
		break;
	}
}

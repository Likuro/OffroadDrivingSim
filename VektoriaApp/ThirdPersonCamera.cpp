#include "ThirdPersonCamera.h"

void ThirdPersonCamera::Init(float distance, float height, eAlign alignement, CPlacement* followObject, CCamera* camera)
{
	m_distance = distance;
	m_height = height;
	m_alignement = alignement;
	m_FollowObject = followObject;
	m_Camera = camera;
	m_oldYaw = followObject->GetMat().GetYaw();
	m_yaw = m_oldYaw;

	// Aufbau der Hierarchie
	this->AddPlacement(&m_CameraSwivel);
	m_CameraSwivel.AddCamera(m_Camera);

	this->update(0.0001f);
}

void ThirdPersonCamera::update(float fTimeDelta)
{
	CHVector followPos = m_FollowObject->GetPos();
	CHVector followDir = m_FollowObject->GetDirection();

	float angle = asinf(m_height / m_distance);
	m_CameraSwivel.RotateX(-angle);
	float yaw = m_FollowObject->GetMat().GetYaw();
	CHMat mat;	
	mat.RotateY(yaw);
	mat.RotateXDelta(-0.03f);//added by Mohamed
	CHVector toCamera(0.f, m_height, (m_height / tan(angle)));

	// Vektor zur Camera wird um den Zoomfaktor skaliert
	toCamera *= m_zoom;
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
	case eAlignZAxisNegative:
		this->Translate(followPos.x, followPos.y + m_height, followPos.z + (m_height / tan(angle)));
		break;
	default:
		break;
	}
	m_oldYaw = m_yaw;
}

void ThirdPersonCamera::zoom(float value)
{
	m_zoom += value;
	if (m_zoom > 1.f)
	{
		m_zoom = 1.f;
	}
	else if (m_zoom < m_maxZoom)
	{
		m_zoom = m_maxZoom;
	}
}


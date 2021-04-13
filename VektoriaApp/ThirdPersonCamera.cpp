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

	//CHVector vecProduct = m_dirCamera ^ followDir;
	//m_dirCamera *= m_stiffness / fTimeDelta;
	//m_dirCamera = (m_dirCamera + followDir) / (1.f + (m_stiffness / fTimeDelta));
	//m_yaw = m_dirCamera.Angle(CHVector(0.f, 0.f, -1.f));
	//m_yaw = std::copysignf(m_yaw, vecProduct.z);

	float difference;
	difference = m_FollowObject->GetMat().GetYaw() - m_oldYaw;
	m_yaw += difference * m_stiffness * fTimeDelta;

	//ULDebug("%1.10f", vecProduct.z);

	float angle = asinf(m_height / m_distance);
	m_CameraSwivel.RotateX(-angle);
	CHMat mat;
	mat.RotateY(m_yaw);
	CHVector toCamera(0.f, m_height, (m_height / tan(angle)));
	// Vektor zur Camera wird um den Zoomfaktor skaliert
	toCamera *= m_zoom;
	toCamera = mat * toCamera;

	switch (m_alignement)
	{
	case eAlignObjDir:
		this->Translate(followPos + toCamera);
		m_CameraSwivel.RotateYDelta(m_yaw);
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


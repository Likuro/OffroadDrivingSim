#include "Game.h"

CGame::CGame(void)
{
	//Mandy war hier hihi
	//Denis war hier
	//lulz
}

CGame::~CGame(void)
{
}

void CGame::Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash)
{
	srand(time(NULL));

	// Hier die Initialisierung Deiner Vektoria-Objekte einfügen:
	m_zr.Init(psplash);
	m_zc.Init(QUARTERPI);
	// m_zf.SetApiRender(eApiRender_DirectX11_Shadermodel50_Monolight);
	m_zf.Init(hwnd, procOS); 
	m_zv.InitFull(&m_zc);
	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f), CColor(1.0f, 1.0f, 1.0f));

	m_zr.AddFrame(&m_zf);
	m_zf.AddViewport(&m_zv);
	m_zr.AddScene(&m_zs);
	m_zs.AddLightParallel(&m_zl);

	// 2 Dummy Materials
	m_MRed.MakeTextureDiffuse("textures\\red_image.jpg");
	m_MGreen.MakeTextureDiffuse("textures\\green_image.jpg");

	// Dummy Kugel
	m_zs.AddPlacement(&m_zpSphere);
	m_zgSphere.Init(1.f, &m_MRed, 50, 50);
	m_zpSphere.SetTranslationSensitivity(15.f);
	m_zpSphere.SetRotationSensitivity(2.f);
	m_zpSphere.AddGeo(&m_zgSphere);

	// Camera
	TPCamera.Init(80.f, 30.f, eAlignZAxisPositive, &m_zpSphere, &m_zc);
	m_zs.AddPlacement(&TPCamera);
	//m_zs.AddPlacement(&m_zpCamera);
	//m_zpCamera.AddCamera(&m_zc);
	
	//m_zpCamera.SetPointing(&m_zpSphere);
	//m_zpCamera.RotateYDelta(PI);
	//m_zpCamera.RotateXDelta(PI);
	//m_zpCamera.PlaceSphericalGlobal(200.f, PI, -QUARTERPI, m_zpSphere);

	m_zf.AddDeviceKeyboard(&m_Keyboard);
	m_zf.AddDeviceGameController(&m_Controller);

	// Healthbar
	Health = new HealthBar(&m_MRed, &m_zv, 100, 100, 0.7f, 0.9f, 0.25f, 0.05f);
	// Speedometer
	Speedometer = new ProgressBar(&m_MRed, &m_zv, 100, 0, 0.05f, 0.9f, 0.25f, 0.05f);

	// ItemManager
	Items = new ItemManager(25, &m_zpSphere);

	//RoadMaster erstellen
	//Placement für den RoadManager
	m_zs.AddPlacement(&drivingScenePlacement);
	this->RoadMaster = new RoadManager;
	RoadMaster->init(&drivingScenePlacement, Items);
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	m_zr.Tick(fTimeDelta);
	timetick++;
	// Tastatur Steuerung
	// Links/Rechts Verschiebung
	//if (m_Keyboard.KeyPressed(DIK_A))
	//{
	//	if (m_Keyboard.KeyPressed(DIK_D))
	//		fAD = 0.f;
	//	else
	//		fAD = -1.f;
	//}
	//else if (m_Keyboard.KeyPressed(DIK_D))
	//	fAD = 1.f;
	//else
	//	fAD = 0.f;
	// Vor/Zurück Verschiebung
	if (m_Keyboard.KeyPressed(DIK_W))
	{
		if (m_Keyboard.KeyPressed(DIK_S))
			fSW = 0.f;
		else
			fSW = -1.f;
	}
	else if (m_Keyboard.KeyPressed(DIK_S))
		fSW = 1.f;
	else
		fSW = 0.f;
	// Hoch/Runter Verschiebung
	if (m_Keyboard.KeyPressed(DIK_LSHIFT))
	{
		if (m_Keyboard.KeyPressed(DIK_SPACE))
			fFR = 0.f;
		else
			fFR = -1.f;
	}
	else if (m_Keyboard.KeyPressed(DIK_SPACE))
		fFR = 1.f;
	else
		fFR = 0.f;
	// Links/Rechts Drehung
	if (m_Keyboard.KeyPressed(DIK_A))
	{
		if (m_Keyboard.KeyPressed(DIK_D))
			fLR = 0.f;
		else
			fLR = -1.f;
	}
	else if (m_Keyboard.KeyPressed(DIK_D))
		fLR = 1.f;
	else
		fLR = 0.f;
	// Hoch/Runter Drehung 
	//!Vorsicht funktioniert bei Third - Person - Camera nicht so gut... (überhaupt nicht!)!//
	//if (m_Keyboard.KeyPressed(DIK_UP))
	//{
	//	if (m_Keyboard.KeyPressed(DIK_DOWN))
	//		fUD = 0.f;
	//	else
	//		fUD = -1.f;
	//}
	//else if (m_Keyboard.KeyPressed(DIK_DOWN))
	//	fUD = 1.f;
	//else
	//	fUD = 0.f;

	m_zpSphere.MoveTerrain(fTimeDelta, fAD, fSW, fFR, fLR, fUD, RoadMaster->getGeosFrontal(), RoadMaster->getGeosGround(), fHeightEye, fHeightRay, hitpointCollision, hitpointGround, true, eMoveFlightKind_Ballistic);
	TPCamera.update();

	//m_zpCamera.RotateY(PI);
	//m_zpCamera.RotateXDelta(atanf(20.f/100.f));
	//m_zpCamera.TranslateZDelta(m_zpSphere.GetPos().GetZ() - 100.f);
	//m_zpCamera.TranslateYDelta(m_zpSphere.GetPos().GetY() + 20.f);
	//m_zpCamera.TranslateXDelta(m_zpSphere.GetPos().GetX());

	// Controller Steuerung
	if (abs(m_Controller.GetRelativeX()) > 0.1)		// Deadzone
	{
		m_zpSphere.TranslateXDelta(-0.2f*(m_Controller.GetRelativeX()*controllerSpeed));
	}
	if (abs(m_Controller.GetRelativeY()) > 0.1)		// Deadzone
	{
		m_zpSphere.TranslateZDelta(0.2f*(-m_Controller.GetRelativeY()*controllerSpeed));
	}
	if (abs(m_Controller.GetRelativeRX()) > 0.1)
	{
		m_zpCamera.RotateYDelta(0.025f * (-m_Controller.GetRelativeRX() * controllerSpeed));
	}
	//if (abs(m_Controller.GetRelativeRY()) > 0.1)
	//{
	//	m_zpCamera.RotateXDelta(0.025f * (m_Controller.GetRelativeRY() * controllerSpeed));
	//}
	//if (abs(m_Controller.GetRelativeRZ()) > 0.1)
	//{
	//	m_zpSphere.TranslateYDelta(0.05f * (m_Controller.GetRelativeRZ() * controllerSpeed));
	//}

	// HealthBar Test
	if (m_Keyboard.KeyDown(DIK_Q))
	{
		Health->changeHealth(-10.f);
	}

	// Speedometer Test
	if (m_Keyboard.KeyPressed(DIK_E))
	{
		Speedometer->progressValue += 0.05f;
		Speedometer->update();
	}
	else
	{
		Speedometer->progressValue -= 0.005f;
		Speedometer->update();
	}

	// nur alle 5k Ticks -- RoadMaster
	if (timetick == 2200) {

		this->RoadMaster->updateRoad();

		timetick = 0;
	}

	// ItemManager
	Items->update(fTime, fTimeDelta);

}

void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
	// Hier kannst Du dann die Auflösung des Viewports neu einstellen:
	m_zf.ReSize(iNewWidth, iNewHeight);
}


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
	// Hier die Initialisierung Deiner Vektoria-Objekte einfügen:
	m_zr.Init(psplash);
	m_zc.Init(QUARTERPI);
	// m_zf.SetApiRender(eApiRender_DirectX11_Shadermodel50_Monolight);
	m_zf.Init(hwnd, procOS); 
	m_zv.InitFull(&m_zc);
	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f), CColor(1.0f, 1.0f, 1.0f));

	m_MRed.MakeTextureDiffuse("textures\\red_image.jpg");
	m_MGreen.MakeTextureDiffuse("textures\\green_image.jpg");

	m_zgSphere.Init(1.5F, &m_MRed, 50, 50);

	m_zr.AddFrame(&m_zf);
	m_zf.AddViewport(&m_zv);
	m_zr.AddScene(&m_zs);

	//Placement für den RoadManager
	m_zs.AddPlacement(&drivingScenePlacement);

	m_zs.AddPlacement(&m_zpSphere);
	m_zs.AddPlacement(&m_zpCamera);
	m_zs.AddLightParallel(&m_zl);
	m_zpCamera.AddCamera(&m_zc);
	m_zpSphere.AddGeo(&m_zgSphere);

	m_zpCamera.TranslateZ(200.0f);
	m_zf.AddDeviceKeyboard(&m_Keyboard);
	m_zf.AddDeviceGameController(&m_Controller);

	// Healthbar
	Health = new HealthBar(&m_MRed, &m_zv, 100, 100, 0.7f, 0.9f, 0.25f, 0.05f);
	// Speedometer
	Speedometer = new ProgressBar(&m_MRed, &m_zv, 100, 0, 0.05f, 0.9f, 0.25f, 0.05f);

	//RoadMaster erstellen
	this->RoadMaster = new RoadManager;
	RoadMaster->init(&drivingScenePlacement);
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	m_zr.Tick(fTimeDelta);
	timetick++;

	// Controller Steuerung
	if (abs(m_Controller.GetRelativeX()) > 0.1)
	{
		m_zpSphere.TranslateXDelta(m_Controller.GetRelativeX()*controllerSpeed);
	}
	if (abs(m_Controller.GetRelativeY()) > 0.1)
	{
		m_zpSphere.TranslateYDelta(-m_Controller.GetRelativeY()*controllerSpeed);
	}

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
	if (timetick == 5000) {

		this->RoadMaster->updateRoad();

		timetick = 0;
	}
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


#pragma once
#include "Vektoria/Root.h"

using namespace Vektoria;

// hier Szenen eintragen für einfacheres Switchen
enum eSceneType {main, game};

class TemplateScene : public CPlacement
{
public:
	virtual void Init(CScene* scene, CViewport* viewport, CDeviceCursor* cursor, CDeviceKeyboard* keyboard) = 0;
	virtual void update(float fTime, float fTimeDelta) = 0;
	virtual void reset() = 0;
	CCamera* getCamera()
	{
		return &m_Camera;
	}
	COverlay* getOverlay()
	{
		return &m_OvRoot;
	}
	eSceneType getNextScene()
	{
		return m_nextScene;
	}
	bool getChange()
	{
		return m_changeScene;
	}
	virtual void setup() 
	{
		m_doSetup = false;
	}
	bool getSetup()
	{
		return m_doSetup;
	}
	void setSetup(bool s)
	{
		m_doSetup = s;
	}
	void setRoot(CRoot* tmp_Root)
	{
		m_Root = tmp_Root;
	}

protected:
	CScene* m_Scene;
	CViewport* m_Viewport;
	COverlay m_OvRoot;
	CCamera m_Camera;
	eSceneType m_nextScene = main;
	bool m_changeScene = false;
	bool m_doSetup = false;
	CRoot* m_Root;
};


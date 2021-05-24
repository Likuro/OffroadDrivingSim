#pragma once
#include "Vektoria/Root.h"

using namespace Vektoria;

// hier Szenen eintragen für einfacheres Switchen
enum eSceneType {main, game};

class TemplateScene : public CScene
{
public:
	virtual void Init(CDeviceCursor* cursor, CDeviceKeyboard* keyboard) {};
	virtual void update(float fTime, float fTimeDelta) = 0;
	virtual void reset()
	{
		m_changeScene = false;
	}
	CViewport* getViewport()
	{
		return &m_Viewport;
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

protected:
	// Viewport
	CViewport m_Viewport;
	eSceneType m_nextScene = main;
	bool m_changeScene = false;
	bool m_doSetup = false;
};


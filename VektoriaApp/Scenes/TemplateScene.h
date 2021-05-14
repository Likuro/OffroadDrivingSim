#pragma once
#include "Vektoria/Root.h"

using namespace Vektoria;

// hier Szenen eintragen für einfacheres Switchen
enum eSceneType {main, game};

class TemplateScene : public CScene
{
public:
	virtual void Init(CDeviceCursor* cursor, CDeviceKeyboard* keyboard) = 0;
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

protected:
	// Viewport
	CViewport m_Viewport;
	eSceneType m_nextScene = main;
	bool m_changeScene = false;
};


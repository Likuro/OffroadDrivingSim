#include "GuiSlider.h"

namespace Vektoria
{
	void CGuiSlider::Init(CDeviceCursor* deviceCursor, CWritingFont* font)
	{
		this->Init(deviceCursor, font, m_zfrBase);
	}

	void CGuiSlider::Init(CDeviceCursor* deviceCursor, CWritingFont* font, CFloatRect& floatRect)
	{
		this->Init(deviceCursor, font, m_fMin, m_fMax, m_fDefault, m_fStep, m_zfrBase);
	}

	void CGuiSlider::SetM_fmax(float max) {
		m_fMax = max;
		m_fRange = m_fMax - m_fMin;
		m_fValueToPositionFactor = (m_fStep / m_fRange) * (1.0f - m_fHandleWidth) * m_fStepInverse;
		if (m_fValue > max) {
			m_fValue = max;
			m_zfrHandle.SetXPos((max - m_fMin) * m_fValueToPositionFactor);
		}
		
		
		ReSize();
		m_zoHandle.SetRect(m_zfrHandle);
		m_zwValue.PrintFloat(m_fValue);
		m_bIsUpdating = true;
	}

	void CGuiSlider::Init(CDeviceCursor* deviceCursor, CWritingFont* font, float fMin, float fMax, float fDefault, float fStep)
	{
		this->Init(deviceCursor, font, fMin, fMax, fDefault, fStep, m_zfrBase);
	}

	void CGuiSlider::Init(CDeviceCursor* deviceCursor, CWritingFont* font, float fMin, float fMax, float fDefault, float fStep, CFloatRect& floatRect)
	{
		CGuiElement::Init(deviceCursor, font, floatRect);
		m_acName = "CGuiSlider";

		// Init parameters
		m_fMin = fMin;
		m_fMax = fMax;
		m_fDefault = fDefault;
		m_fRange = m_fMax - m_fMin;
		m_fStep = fStep;
		m_fStepInverse = 1.0f / m_fStep;
		m_fValueToPositionFactor = (m_fStep / m_fRange) * (1.0f - m_fHandleWidth) * m_fStepInverse;


		// Styling base overlay
		m_zmBase.MakeTextureSprite("textures\\gui\\GuiElement_Background.jpg");
		m_zmBase.SetTransparency(0.0f);

		// Styling Interactable
		m_zoInteractable.SetTransparency(1.0f);
		m_zoInteractable.SetRect(CFloatRect(0.05f, 0.4f, 0.9f, 0.5f));

		// Label writing
		m_zwLabel.m_ixChars = 12;
		m_zwLabel.SetRect(CFloatRect(0.05f, 0.15f, 0.6f, 0.2f));

		// Value writing
		m_zwValue.Init(CFloatRect(0.65f, 0.15f, 0.3f, 0.2f), 4, m_pwfFont);
		m_zwValue.SetInnerOn();
		m_zwValue.SetLayer(m_zwLabel.GetLayer());
		AddWriting(&m_zwValue);

		// Styling Handle
		m_zmHandleBackground.MakeTextureSprite("textures\\gui\\GuiSlider_Handle.png");
		m_zmHandleBackground.SetTransparencyOn();

		// Initialize Handle
		m_zfrHandle.SetXSize(m_fHandleWidth);
		m_zoHandle.Init(&m_zmHandleBackground, m_zfrHandle);
		m_zoHandle.SetInnerOn();
		m_zoInteractable.AddOverlay(&m_zoHandle);

		// Init & Styling Track
		m_zmTrackVisual.MakeTextureSprite("textures\\gui\\GuiSlider_Track.png");
		m_zmTrackVisual.SetTransparencyOn();
		m_zoTrackVisual.Init(&m_zmTrackVisual, CFloatRect(0.0f, 0.45f, 1.0f, 0.1f));
		m_zoTrackVisual.SetInnerOn();
		m_zoInteractable.AddOverlay(&m_zoTrackVisual);

		SetValue(m_fDefault);
	}

	float CGuiSlider::GetValue()
	{
		return m_fValue;
	}
	
	void CGuiSlider::SetValue(float value)
	{
		if (value <= m_fMin) {
			m_fTmpValue = m_fMin;
		}
		else if (value >= m_fMax) {
			m_fTmpValue = m_fMax;
		}
		else {
			// Round value to closest step
			m_fTmpValue = round(value * m_fStepInverse) * m_fStep;

			if (m_fTmpValue == -0.0f) {
				m_fTmpValue = 0.0f;
			}
		}

		if (m_fValue != m_fTmpValue) {
			m_fValue = m_fTmpValue;

			// Update handle
			m_zfrHandle.SetXPos((m_fValue - m_fMin) * m_fValueToPositionFactor);
			m_zoHandle.SetRect(m_zfrHandle);

			// Update value writing
			m_zwValue.PrintFloat(m_fValue);
		}

		m_bIsUpdating = true;
	}

	bool CGuiSlider::HasUpdated()
	{
		return m_bHasUpdated;
	}

	void CGuiSlider::SetLayerGui(float layer)
	{
		CGuiElement::SetLayerGui(layer);

		m_zoHandle.SetLayer(m_zoInteractable.GetLayer());
		m_zoTrackVisual.SetLayer(m_zoInteractable.GetLayer());
	}

	void CGuiSlider::ReSize()
	{
		CGuiElement::ReSize();

		CFloatRect frAbsoluteInteractable = GetRectAbsolute(&m_zoInteractable);

		float fHandleHeight = m_fHandleWidth * frAbsoluteInteractable.GetXSize() / frAbsoluteInteractable.GetYSize();
		if (m_pviewport != nullptr) {
			fHandleHeight = (m_fHandleWidth * frAbsoluteInteractable.GetXSize() * (float)m_pviewport->m_iWidth) / (frAbsoluteInteractable.GetYSize() * (float)m_pviewport->m_iHeight);
		}

		// Update rect size and position
		m_fPosAbsX = frAbsoluteInteractable.GetXPos();
		m_fCursorToValueFactor = m_fRange / (frAbsoluteInteractable.GetXSize() * (1.0f - 0.5f * m_fHandleWidth));

		// Update Handle
		m_zfrHandle.SetYPos(0.5f - fHandleHeight * 0.5f);
		m_zfrHandle.SetYSize(fHandleHeight);
		m_zoHandle.SetRect(m_zfrHandle);
	}

	void CGuiSlider::Tick(float& fTimeDelta, CFloatRect& floatrectFather)
	{
		if (IsFirstTick()) {
			m_bIsUpdating = false; // Don't trigger HasUpdated() on the first tick
		}
			m_zoHandle.SetRect(m_zfrHandle);

		CGuiElement::Tick(fTimeDelta, floatrectFather);

		m_bHasUpdated = false;

		if (m_bIsGrabbed) {
			SetValue((m_pdc->m_frxFrame - m_fPosAbsX) * m_fCursorToValueFactor + m_fMin);
		} else if (m_bIsUpdating) {
			m_bHasUpdated = true;
			m_bIsUpdating = false;
		}
	}
}

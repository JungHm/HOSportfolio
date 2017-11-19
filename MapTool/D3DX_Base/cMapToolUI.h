#pragma once
#include "cUIButton.h"

class cUIObject;

enum
{
	UI_IMAGE_PANEL = 11,
	UI_BUTTON_OK = 21,
	UI_BUTTON_CANCEL,
};

class cMapToolUI
{
private:
	LPD3DXSPRITE	m_pSprite;
	D3DXIMAGE_INFO  m_stImageInfo;
	cUIObject*		m_pRootUI;

public:
	cMapToolUI();
	~cMapToolUI();

	void Setup();
	void Update();
	void Render();
};


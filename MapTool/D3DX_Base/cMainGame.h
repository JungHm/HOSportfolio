#pragma once
#include "cUIButton.h"

class cMapTool;
class cUIObject;

enum
{
	UI_IMAGE_CENTER_PANEL = 11,
	UI_IMAGE_LEFT_PANEL = 21,
	UI_IMAGE_RIGHT_PANEL = 31,
	UI_LEFT_BUTTON = 41,
	UI_RIGHT_BUTTON = 51,
	UI_OBJ_IMAGE
};

class cMainGame : public iButtonDelegate
{
private:
	cMapTool*	 m_pMapTool;
	cUIObject*		m_pRootUI;
	LPD3DXSPRITE	m_pSprite;
	D3DXIMAGE_INFO  m_stImageInfo;

public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render();

	void UISetup();
	virtual void OnClick(cUIButton* pSender) override;

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};


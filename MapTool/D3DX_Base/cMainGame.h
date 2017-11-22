#pragma once
#include "cUIButton.h"
#include "cUIImageView.h"

class cMapTool;
class cUIObject;
class cSkyBox;

enum
{
	UI_TOOLMODE_NONE,
	UI_TOOLMODE_OBJ,
	UI_TOOLMODE_BOX,
	UI_TOOLMODE_NODE,
	UI_TOOLMODE_ILNE,
	UI_IMAGE_CENTER_PANEL = 11,
	UI_IMAGE_LEFT_PANEL = 21,
	UI_IMAGE_RIGHT_PANEL = 31,
	UI_LEFT_BUTTON = 41,
	UI_RIGHT_BUTTON = 51,
	UI_SAVE_BUTTON = 61,
	UI_LOAD_BUTTON = 71,
	UI_REMOVE_BUTTON = 81,
	UI_STATE_IMAGE,
	UI_REMOVE_IMAGE,
	UI_SAVE_IMAGE,
	UI_LOAD_IMAGE,
	UI_OBJ_IMAGE,
	UI_OBJ_IMAGE2,
	UI_OBJ_IMAGE3
};

class cMainGame : public iButtonDelegate
{
private:
	cMapTool*		m_pMapTool;
	cUIObject*		m_pRootUI;
	LPD3DXSPRITE	m_pSprite;
	D3DXIMAGE_INFO  m_stImageInfo;
	string			m_sUIObj[OBJNUM]; // 텍스쳐 파일 이름
	cUIImageView*	m_pImageCursor;
	cUIImageView*	m_pToolModeView;
	cSkyBox*		m_pSkyBox;
	int				m_nIndex;
	POINT			m_nMousePos;

	DWORD			m_dAttack;
	
//private:
//	wstring			m_sPath;
//	int				m_nKey;
//	float			m_fBlendTime;
//	float			m_fPassedBlendTime;
//	int				m_nState;

public:
	cMainGame();
	~cMainGame();
	void ChangeAni();
	void Setup();
	void Update();
	void Render();

	void UISetup();
	virtual void OnClick(cUIButton* pSender) override;

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};


#pragma once
#include "cUIObject.h"

class cUIButton;

class iButtonDelegate
{
public:
	virtual void OnClick(cUIButton* pSender) = 0;
};

class cUIButton : public cUIObject
{
protected:
	enum BUTTONSTATE
	{
		BTN_NORMAL,
		BTN_MOUSE_OVER,
		BTN_SELECTED,
		BTN_NUM
	};

	BUTTONSTATE			m_eButtonState;
	LPDIRECT3DTEXTURE9  m_pArrTexture[BTN_NUM];
	SYNTHESIZE(iButtonDelegate*, m_pDelegate, Delegate);

public:
	cUIButton();
	virtual ~cUIButton();

	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Update();
	void SetTexture(char* szNormal, char* szOver, char* szSelected);
};


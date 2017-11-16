#pragma once
#include "cUIObject.h"

class cUIImageView : public cUIObject
{
protected:
	LPDIRECT3DTEXTURE9 m_pTexture;

public:
	cUIImageView();
	virtual ~cUIImageView();

	virtual void Render(LPD3DXSPRITE pSprite) override;
	void SetTexture(char* szFullPath);
};


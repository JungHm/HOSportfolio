#pragma once
#include "cUIObject.h"

class cUIObjView : public cUIObject
{
protected:
	LPDIRECT3DTEXTURE9	m_pTexture;
	OBJECTKIND			m_eObjKind;

public:
	cUIObjView();
	virtual ~cUIObjView();

//	void SetTexture(char* szFullPath);
//	virtual void Render(LPD3DXSPRITE pSprite) override;
};


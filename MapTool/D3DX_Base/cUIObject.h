#pragma once
#include "cObject.h"

class cUIObject : public cObject
{
protected:
	vector<cUIObject*>	m_vecChild;
	D3DXMATRIXA16		m_matWorld;
	D3DXMATRIXA16		m_matScal;

	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(D3DXVECTOR3, m_vScaling, Scaling);
	SYNTHESIZE(cUIObject*, m_pParent, Parent);
	SYNTHESIZE(ST_UI_SIZE, m_sSize, Size);
	SYNTHESIZE(bool, m_isHidden, Hidden);
	SYNTHESIZE(int, m_nTag, Tag);

public:
	cUIObject();
	virtual ~cUIObject();

	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);

	cUIObject* FindChildByTag(int nTag);
	void SetPosition(int nX, int nY, int nZ = 0);
	void AddChild(cUIObject* pChild);
	void Destroy();
};


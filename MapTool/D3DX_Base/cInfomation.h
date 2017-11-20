#pragma once

class cInfomation
{
private:
	LPD3DXFONT		m_pFont;
	SYNTHESIZE(float, m_fScale, Scale);
	SYNTHESIZE(float, m_fRotation, Rotation);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(int, m_eObjKind, ObjKind);
	SYNTHESIZE(int, m_nObjNum, ObjNum);

public:
	cInfomation();
	~cInfomation();

	void Setup();
	void Render();
};


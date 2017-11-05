#pragma once
class cCube
{
protected:
	std::vector<ST_PNT_VERTEXT>	m_vecVertex;

	D3DXMATRIXA16				m_matLocalTM;
	D3DXMATRIXA16				m_matWorldTM;

	D3DXVECTOR3					m_vLocalPos;


	std::vector<cCube*>			m_vecChild;

	float						m_fRotX;

	SYNTHESIZE(D3DXMATRIXA16*, m_pParentWorldTM, ParentWorldTM);
	SYNTHESIZE(float, m_fRotDeltaX, RotDeltaX);
	
public:
	cCube();
	virtual ~cCube();

	void AddChild(cCube* pChild);
	void Destroy();

	virtual void Setup();
	void Update();
	void Render();
};


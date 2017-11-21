#pragma once
class cFrustum
{
private:
	std::vector<D3DXVECTOR3>	m_vecProjVertex;
	std::vector<D3DXVECTOR3>	m_vecWorldVertex;
	std::vector<D3DXPLANE>		m_vecPlane;

public:
	cFrustum();
	~cFrustum();

	void Setup();
	void Update();
	bool IsInside(ST_SPHERE* pSphere);
};


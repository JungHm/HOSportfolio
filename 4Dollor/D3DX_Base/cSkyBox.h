#pragma once

class cObjLoader;

class cSkyBox
{
private:
	cObjLoader*		 m_pObjLoader;
	vector<cMtlTex*> m_vecMtlTex;
	LPD3DXMESH		 m_pMesh;
	D3DXMATRIXA16	 m_matWorld;

public:
	cSkyBox();
	~cSkyBox();

	void Setup();
	void Render();
};


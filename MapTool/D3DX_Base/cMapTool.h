#pragma once

class cGrid;
class cInfomation;
class cObjLoader;
class cMtlTex;

class cMapTool
{
private:
	D3DXVECTOR3	m_vObjPos;
	bool		m_isPicking;
	bool		m_is

private:
	cGrid*		 m_pGrid;
	cInfomation* m_pInfo;
	cObjLoader*		 m_pObjLoader;
	LPD3DXMESH		 m_pObjMesh;
	vector<cMtlTex*> m_vecObjMtlTex;

public:
	cMapTool();
	~cMapTool();

	void ObjLoaderTestSetup();
	void ObjLoaderTestRender();

	void ObjPicking(LPARAM lParam);
};


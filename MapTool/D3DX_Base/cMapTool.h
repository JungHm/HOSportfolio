#pragma once

class cGrid;
class cObjLoader;
class cMtlTex;

class cMapTool
{
private:
	cGrid*		 m_pGrid;
	cObjLoader*		 m_pObjLoader;
	LPD3DXMESH		 m_pObjMesh;
	vector<cMtlTex*> m_vecObjMtlTex;

public:
	cMapTool();
	~cMapTool();

	void ObjLoaderTestSetup();
	void ObjLoaderTestRender();
};


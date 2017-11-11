#pragma once

class cGrid;
class cInfomation;
class cObjLoader;
class cMtlTex;

class cMapTool
{
private:
	cGrid*			m_pGrid;
	cInfomation*	m_pInfo;
	cObjLoader*		m_pObjLoader;
	map<int, vector<cMtlTex*>>	 m_mapObjMtlTex;

private:
	OBJECT		m_sObj;
	LPD3DXMESH	m_pObjMesh[OBJNUM];	  // 매쉬로 생성
	int			m_nIndex;			  // 인덱스
	bool		m_isPicking;		  // 피킹 중인 상태
	bool		m_isAllocate;		  // 배치 상태

public:
	cMapTool();
	~cMapTool();

	void Setup();
	void Update();
	void Render();

	void SetUpObj();
	void ObjPicking(IN UINT message, IN WPARAM wParam, IN LPARAM lParam);
	void ObjSelect();
};


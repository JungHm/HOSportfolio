#pragma once

class cGrid;
class cInfomation;
class cObjLoader;
class cMtlTex;
class cSaveLoad;

class cMapTool
{
private:
	cGrid*						m_pGrid;
	cInfomation*				m_pInfo;
	cObjLoader*					m_pObjLoader;
	cSaveLoad*					m_pSaveLoad;
	map<int, vector<cMtlTex*>>	m_mapObjMtlTex;

private:
	OBJECT		m_sObj;				  // 현재 마우스로 움직이는 오브젝트 정보
	LPD3DXMESH	m_pObjMesh[OBJNUM];	  // 로드한 매쉬를 종류별로 선택지정 
	int			m_nIndex;			  // 선택중인 오브젝트의 인덱스
	bool		m_isPicking;		  // 피킹 중인 상태
	bool		m_isAllocate;		  // 배치 상태
	string		m_sFileName[OBJNUM];  // 파일 이름

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


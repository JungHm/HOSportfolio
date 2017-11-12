#pragma once

class cObjLoader;

class cSaveLoad
{
private:
	cObjLoader*					m_pObjLoader;		 // 오브젝트 로더 클래스
	vector<OBJECT>				m_vecFieldObj;		 // 필드에 배치되는 오브젝트
	string						m_sFileName[OBJNUM]; // 파일 이름
	LPD3DXMESH					m_pObjMesh[OBJNUM];	 // 로드한 매쉬를 종류별로 선택지정 
	map<int, vector<cMtlTex*>>	m_mapObjMtlTex;		 // 매쉬의 매테리얼, 텍스쳐를 담은 벡터 를 담은 맵

public:
	cSaveLoad();
	~cSaveLoad();

	// 저장 된 파일의 이름 Get
	string GetFileName(int nIndex) { return m_sFileName[nIndex]; }
	// 로더 된 매쉬 Get
	LPD3DXMESH GetObjMesh(int nIndex) { return m_pObjMesh[nIndex]; }
	// 도더 된 메터리얼, 텍스처 정보 Get
	vector<cMtlTex*> GetMapObjMtltex(int nkey) { return m_mapObjMtlTex[nkey]; }
	// 필드에 배치되는 오브젝트 생성 함수
	void CreateObj(IN int nKind, IN LPD3DXMESH pMesh, IN vector<cMtlTex*> vecValue, IN string sFileName, IN D3DXVECTOR3 vScal, IN D3DXVECTOR3 vPos, IN float fAngleY);
	// 배치 된 오브젝터 랜더
	void CreateObjRender();
	// 오브젝트 뒤에서 하나씩 삭제
	void RemoveObj();
	// 오브젝트 세이브
	void SaveFieldObj();
	// 오브젝트 로더
	void LoadFieldObj();
};


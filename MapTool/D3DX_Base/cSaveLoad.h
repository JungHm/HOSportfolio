#pragma once

class cObjLoader;

class cSaveLoad
{
private:
	cObjLoader*					m_pObjLoader;				// 오브젝트 로더 클래스
	LPD3DXMESH					m_pObjMesh[OBJNUM];			// 로드한 매쉬를 종류별로 선택지정 
	string						m_sFileName[OBJNUM];		// 파일 이름
	map<int, vector<cMtlTex*>>	m_mapObjMtlTex;				// 매쉬의 매테리얼, 텍스쳐를 담은 벡터 를 담은 맵
	D3DMATERIAL9				m_mtlNone;					// 선택 되지않았을 때 노드 메터리얼
	D3DMATERIAL9				m_mtlSelected;				// 선택 되었을 때 노드 메터리얼
	SYNTHESIZE(vector<OBJECT>, m_vecFieldObj, FieldObj);	// 필드에 배치되는 오브젝트
	SYNTHESIZE(vector<ST_BOX>, m_vecFieldBox, FielBox);		// 필드에 배치되는 충돌 박스
	SYNTHESIZE(vector<ST_COST>, m_vecCost, Cost);			// 다익스트라 길찾기 갱신 값
	SYNTHESIZE_PASS_BY_REF(vector<ST_SPHERE_NODE>, m_vecFieldNodeSphere, FieldNodeSphere); // 필드에 배치되는 다익스트라 노드 스페어
	SYNTHESIZE_PASS_BY_REF(vector<ST_PC_VERTEXT>, m_vecNodeLine, NodeLinde);			   // 각 노드들의 연결 라인
	
public:
	cSaveLoad();
	~cSaveLoad();

	// 저장 된 파일의 이름 Get
	string GetFileName(int nIndex) { return m_sFileName[nIndex]; }
	// 로더 된 매쉬 Get
	LPD3DXMESH GetObjMesh(int nIndex) { return m_pObjMesh[nIndex]; }
	// 도더 된 메터리얼, 텍스처 정보 Get
	vector<cMtlTex*> GetMapObjMtltex(int nkey) { return m_mapObjMtlTex[nkey]; }
	// 필드에 배치된 오브젝트 개수 Get
	int GetFieldObjNum() { return m_vecFieldObj.size(); }
	// 필드에 배치되는 충돌박스 생성 함수
	void CreateBox(IN LPD3DXMESH pMesh, IN D3DXVECTOR3 vScal, IN D3DXVECTOR3 vPos, IN float fAngleY);
	// 필드에 배치되는 오브젝트 생성 함수
	void CreateObj(IN int nKind, IN LPD3DXMESH pMesh, IN vector<cMtlTex*> vecValue, IN string sFileName, IN D3DXVECTOR3 vScal, IN D3DXVECTOR3 vPos, IN float fAngleY);
	// 필드에 배치되는 다익스트라 노드 생성 함수
	void CreateNodeSphere(IN LPD3DXMESH pMesh, IN D3DXVECTOR3 vPos, IN vector<NODE> vecNode);
	// 다익스트라 노드 갱신값 초기화
	void CostSetup(IN int nSize);
	// 배치 된 오브젝트 랜더
	void CreateObjRender();
	// 오브젝트 뒤에서 하나씩 삭제
	void RemoveObj();
	// 충돌 박스 뒤에서 하나씩 삭제
	void RemoveBox();
	// 노드 뒤에서 하나씩 삭제, 연결라인 은 2개씩 삭제
	void RemoveNode();
	// 오브젝트, 충돌박스, 노드, 노드 연결라인 세이브
	void SaveFieldObj();
	// 오브젝트, 충돌박스, 노드, 노드 연력라인 로더
	void LoadFieldObj();
};
#pragma once

class cGrid;
class cInfomation;
class cSaveLoad;
class cHeightMap;

// 현재 맵툴에서 배치중인 것이 무엇인지 알려주는 상태
enum ALLOCATE_STATE
{
	ALLOCATE_NONE,					// 아무고토 하지 않는 상태
	ALLOCATE_OBJECT,				// 오브젝트 배치 상태
	ALLOCATE_COLLISION_BOX,			// 충돌 박스 배치 상태
	ALLOCATE_DIJKSTRA_NODE_SPHERE,	// 다익스트라 노드 스페어 배치 상태
	ALLOCATE_NODE_LINE				// 노드 연결 라인 배치 상태
};

class cMapTool
{
private:
	cGrid*			m_pGrid;			// 그리드 클래스
	cSaveLoad*		m_pSaveLoad;		// 세이브 로드 클래스
	cHeightMap*		m_pHeightMap;		// 높이맵 클래스
	cInfomation*	m_pInfo;			// 맵툴 정보	클래스
	OBJECT			m_sObj;				// 현재 마우스로 움직이는 오브젝트 정보
	ST_BOX			m_sCollisionBox;;	// 충돌용 박스
	ST_SPHERE_NODE	m_sNodeSphere;		// 다익스트라 알고리즘의 노드 지정용 스페어
	bool			m_isPicking;		// 피킹 중인 상태
	SYNTHESIZE(int, m_nIndex, Index);	// 선택중인 오브젝트의 인덱스
	SYNTHESIZE(int, m_eAllocateState, AllocateState);	// 현재 배치상태
	int				m_nCount;			// 노드 연결 카운트
	float			m_fStartX, m_fStartZ;
	float			m_fEndX, m_fEndZ;
	int				m_nFirstIndex;

public:
	cMapTool();
	~cMapTool();

	void Setup();
	void Update();
	void Render();
	
	// 피킹 상태인 오브젝트 초기화
	void SetUpPickingObj();
	// 오브젝트 피킹, 배치전 S * R * T 조정 함수
	void ObjPicking(IN UINT message, IN WPARAM wParam, IN LPARAM lParam);
	// 오브젝트 세이브
	void ObjSave();
	// 오브젝트 로드
	void ObjLoad();
	// 오브젝트 지우기
	void ObjRemove();
};


#pragma once

class cGrid;
class cInfomation;
class cSaveLoad;
class cHeightMap;

class cMapTool
{
private:
	cGrid*			m_pGrid;			// 그리드 클래스
	cInfomation*	m_pInfo;			// 맵툴 정보	클래스
	cSaveLoad*		m_pSaveLoad;		// 세이브 로드 클래스
	OBJECT			m_sObj;				// 현재 마우스로 움직이는 오브젝트 정보
	cHeightMap*		m_pHeightMap;		// 높이맵 클래스
	SYNTHESIZE(int, m_nIndex, Index);	// 선택중인 오브젝트의 인덱스
	bool			m_isPicking;		// 피킹 중인 상태
	bool			m_isAllocate;		// 배치 준비 상태

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
	// 오브젝트 배치, 삭제, 세이브, 로드
	void ObjAllocate();
};


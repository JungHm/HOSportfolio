#pragma once
#include "iScene.h"

class cUILoadingInGame;
class cUIInGame;
class cGrid;
class cCamera;
class cTessadar;
class cPlayer;
class cSaveLoad;
class cHeightMap;
class cSkyBox;
class cTower;

class cInGame :
	public iScene
{
private:
	cUILoadingInGame*	m_UILoading;
	cUIInGame*			m_UI;

	std::vector<ST_PC_VERTEXT>	m_vecVertex;
	cGrid*		m_pGrid;
	cCamera*	m_pCamera;
	cPlayer*	m_pPlayer;
	cSaveLoad*  m_pLoadMap;
	cHeightMap* m_pHeightMap;
	cSkyBox*    m_pSkyBox;
	cTower*		m_pTower;

private:
	POINT m_ptMouse;
	BOOL  m_isColl;
	float Distance;

	int minionCount;

public:
	cInGame();
	~cInGame();

	virtual void SetUp() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	void tCollision(OUT float* fDistans, IN LPD3DXMESH pObjMesh);
};


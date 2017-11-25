#include "stdafx.h"
#include "cInGame.h"
#include "cUILoadingInGame.h"
#include "cUIInGame.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cTessadar.h"
#include "cPlayer.h"
#include "cSaveLoad.h"
#include "cHeightMap.h"
#include "cSkyBox.h"
#include "cTower.h"

cInGame::cInGame()
{
}

cInGame::~cInGame()
{
}

void cInGame::SetUp()
{
	m_isColl = false;

	g_Particle->Setup();

	m_UILoading = new cUILoadingInGame;
	m_UILoading->setup("cUILoadingInGame");

	m_UI = new cUIInGame;
	m_UI->setup("cInGame");

	m_pLoadMap = new cSaveLoad;
	m_pLoadMap->LoadFieldObj();

	m_pHeightMap = new cHeightMap;
	m_pHeightMap->Setup("HeightMap/", "backGround.raw", "HeightMap.jpg");

	m_pSkyBox = new cSkyBox;
	m_pSkyBox->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup("Grid", "field2.png", 65, 115, 5.0f);

	m_pTower = new cTower;
	m_pTower->Setup(D3DXVECTOR3(-252.370010, 0.100000, -12.779068), D3DXVECTOR3(252.751999, 0.100000, -27.856529));

	cTessadar*	m_pTessadar;
	m_pTessadar = new cTessadar;
	m_pPlayer = new cPlayer;
	m_pPlayer->SetCharacter(m_pTessadar);
	m_pPlayer->Setup();

	//=========미니언===========
	MINIONMANAGER->BlueXfileSetup();
	MINIONMANAGER->RedXfileSetup();
	MINIONMANAGER->BlueSetup();
	MINIONMANAGER->RedSetup();
	MINIONMANAGER->BlueSetup();
	MINIONMANAGER->RedSetup();
	MINIONMANAGER->BlueSetup();
	MINIONMANAGER->RedSetup();
	minionCount = 0;
}

void cInGame::Destroy()
{
	g_Particle->Destroy();
	if (m_UI)
	{
		m_UI->destroy();
		SAFE_DELETE(m_UI);
	}
	if (m_UILoading)
	{
		m_UILoading->destroy();
		SAFE_DELETE(m_UILoading);
	}
	SAFE_DELETE(m_pLoadMap);
	SAFE_DELETE(m_pHeightMap);
	SAFE_DELETE(m_pSkyBox);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pTower);

	SAFE_DELETE(m_pPlayer);
	//m_pRootNode->Destroy();
}

void cInGame::Update()
{
	if (m_pTower)
	{
		m_pTower->Update();
		m_pTower->RedFindEnemy(m_pPlayer->GetSphere());
	}

	m_pPlayer->Update();
	if (m_pPlayer->GetLevel() < 4)//레벨에 따라 스킬 언락
		m_UI->SetSkillUnlock(m_pPlayer->GetLevel(), true);

	if (m_pPlayer->isQcool)
	{
		m_UI->SetSkillUse(1, true);
		m_UI->SetSkillUseCooldown(1, m_pPlayer->coolQ);
	}
	else m_UI->SetSkillUse(1, false);
	if (m_pPlayer->isWcool)
	{
		m_UI->SetSkillUse(2, true);
		m_UI->SetSkillUseCooldown(2, m_pPlayer->coolW);
	}
	else m_UI->SetSkillUse(2, false);
	if (m_pPlayer->isEcool)
	{
		m_UI->SetSkillUse(3, true);
		m_UI->SetSkillUseCooldown(3, m_pPlayer->coolE);
	}
	else m_UI->SetSkillUse(3, false);

	D3DXVECTOR3 pickPosition;
	for (int i = 0; i < m_pGrid->GetPicVertex().size(); i += 3)
	{
		if (IntersectTri(D3DXVec2TransformArray(m_ptMouse.x, m_ptMouse.y),
			m_pGrid->GetPicVertex()[i].p,
			m_pGrid->GetPicVertex()[i + 1].p,
			m_pGrid->GetPicVertex()[i + 2].p,
			pickPosition))
		{
			m_pPlayer->SetMousePos(pickPosition);
			break;
		}
	}

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		D3DXVECTOR3 pickPosition;
		for (int i = 0; i < m_pGrid->GetPicVertex().size(); i += 3)
		{
			if (IntersectTri(D3DXVec2TransformArray(m_ptMouse.x, m_ptMouse.y),
				m_pGrid->GetPicVertex()[i].p,
				m_pGrid->GetPicVertex()[i + 1].p,
				m_pGrid->GetPicVertex()[i + 2].p,
				pickPosition))
			{
				D3DXVECTOR3 dir = pickPosition - m_pPlayer->GetPosition();
				D3DXVec3Normalize(&dir, &dir);
				m_pPlayer->SetDir(dir);
				m_pPlayer->SetFrom(pickPosition);
				break;
			}
		}
	}



	if (m_UI && !m_UILoading)
	{
		m_UI->update();	// ��ư�� ����Ƿ� update
		if (m_UI->GetGameEnd())
		{
			g_Scene->ChangeScene("menu");
		}
	}
	else if (m_UILoading)
	{
		m_UILoading->update();
		if (m_UILoading->GetLoadingEnd())
		{
			m_UILoading->destroy();
			SAFE_DELETE(m_UILoading);
		}
	}

	for (int i = 0; i < m_pLoadMap->GetFielBox().size(); i++)
	{
		tCollision(&Distance, m_pLoadMap->GetFielBox()[i].pMesh);
	}

	std::cout << Distance << std::endl;

	//========미니언==========
	minionCount++;

	int rnd;

	if (minionCount % 1000 == 0)
	{
		MINIONMANAGER->BlueSetup();
		MINIONMANAGER->RedSetup();
		MINIONMANAGER->BlueSetup();
		MINIONMANAGER->RedSetup();
		MINIONMANAGER->BlueSetup();
		MINIONMANAGER->RedSetup();

	}


	MINIONMANAGER->RedUpdate(m_pPlayer->GetPosition());
	MINIONMANAGER->BlueUpdate(m_pPlayer->GetPosition());
}

void cInGame::Render()
{
	if (m_UI && !m_UILoading) m_UI->renderBG();	// ��� ���� ���� ��
	else if (m_UILoading) m_UILoading->renderBG();

	if (m_UI && !m_UILoading) m_UI->render();	// ��� �� UI ��õ� ����
	else if (m_UILoading) m_UILoading->render();

	//g_pSprite->BeginScene();
	//g_pSprite->Render(m_pD3DTexture, NULL, NULL, &D3DXVECTOR3(100, 100, 0), 255);
	//g_pSprite->End();

	if (m_pLoadMap)
		m_pLoadMap->CreateObjRender();

	if (m_pHeightMap)
		m_pHeightMap->Render();

	if (m_pSkyBox)
		m_pSkyBox->Render();

	if (m_pGrid)
		m_pGrid->Render();

	if (m_pTower)
		m_pTower->Render();

	m_pPlayer->Render();

	//=======미니언=======
	MINIONMANAGER->BlueRender();
	MINIONMANAGER->RedRender();
}

void cInGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_ptMouse.x = LOWORD(lParam);
	m_ptMouse.y = HIWORD(lParam);
}

void cInGame::tCollision(OUT float* fDistans, IN LPD3DXMESH pObjMesh)
{
	D3DXIntersect(
		pObjMesh,											//	충돌할 메쉬
		&m_pPlayer->GetPosition(),							//	해당 충돌할 녀석의 포지션
		&m_pPlayer->GetDir(),								//	" 방향
		&m_isColl, NULL, NULL, NULL, fDistans, NULL, NULL);

	//printf_s("%f\n", Distance);

	//std::cout << m_pPlayer->GetPosition().x << " " << m_pPlayer->GetPosition().y << " " << m_pPlayer->GetPosition().z << endl;
	/*std::cout << Distance << std::endl;*/
	//std::cout << m_pPlayer->GetDir().x << " " << m_pPlayer->GetDir().y << " " << m_pPlayer->GetDir().z << endl;
}

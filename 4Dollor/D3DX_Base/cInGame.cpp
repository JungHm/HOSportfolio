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
	m_fDist = 0.0f;

	g_Particle->Setup();

	m_UI = new cUIInGame;
	m_UI->setup("cInGame");


	D3DXVECTOR2 temp;
	g_pTextureManager->AddTexture(L"lichKing/textures/box.png", m_pD3DTexture, &temp);

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
	SAFE_DELETE(m_pLoadMap);
	SAFE_DELETE(m_pHeightMap);
	SAFE_DELETE(m_pSkyBox);
	SAFE_DELETE(m_pGrid);
	SAFE_RELEASE(m_pD3DTexture);
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

<<<<<<< HEAD
	if (m_UI && !m_UILoading)
=======
	if (m_UI)
>>>>>>> 37267a5cbbc467e2262bf3987c6a2e7f8e26ed54
	{
		m_UI->update();	// ��ư�� ����Ƿ� update
		if (m_UI->GetGameEnd())
		{
			g_Scene->ChangeScene("menu");
			return;
		}
	}

<<<<<<< HEAD
	//SphereCollision();
=======
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
>>>>>>> 37267a5cbbc467e2262bf3987c6a2e7f8e26ed54
}

void cInGame::Render()
{
	if (m_UI) m_UI->renderBG();	// ��� ���� ���� ��





	if (m_UI) m_UI->render();	// ��� �� UI ��õ� ����

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

	m_UI->updateBar(true, m_pPlayer->GetPosition(), m_pPlayer->GetHp());
	//m_UI->updateBarMinion(10, { 0,0,0 }, 100);	// 미니언 추가되면 작업

	//=======미니언=======
	MINIONMANAGER->BlueRender();
	MINIONMANAGER->RedRender();

}

void cInGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_ptMouse.x = LOWORD(lParam);
	m_ptMouse.y = HIWORD(lParam);
}

void cInGame::SphereCollision()
{
	for (int i = 0; i < m_pLoadMap->GetFieldObj().size(); i++)
	{
		if (!m_pLoadMap->GetFieldObj()[i].isShow) continue;

		if (getDistance(
			m_pLoadMap->GetFieldObj()[i].vPosition.x,
			m_pLoadMap->GetFieldObj()[i].vPosition.z,
			m_pPlayer->GetPosition().x,
			m_pPlayer->GetPosition().z) < m_pLoadMap->GetFieldObj()[i].sSphere.fRadius)
		{
			break;
		}
	}
}

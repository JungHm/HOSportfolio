#include "stdafx.h"
#include "cInGame.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cTessadar.h"
#include "cPlayer.h"
#include "cUtil.h"
#include "cSaveLoad.h"
#include "cHeightMap.h"
#include "cSkyBox.h"


cInGame::cInGame()
	: m_pGrid(NULL)
	, m_pCamera(NULL)
	, m_pD3DTexture(NULL)
	, m_pLoadMap(NULL)
	, m_pHeightMap(NULL)
	, m_pSkyBox(NULL)
{
}


cInGame::~cInGame()
{
}

void cInGame::SetUp()
{
	D3DXVECTOR2 temp;
	g_pTextureManager->AddTexture(L"lichKing/textures/box.png", m_pD3DTexture, &temp);

	m_pLoadMap = new cSaveLoad;
	m_pLoadMap->LoadFieldObj();

	m_pHeightMap = new cHeightMap;
	m_pHeightMap->Setup("HeightMap/", "backGround.raw", "HeightMap.jpg");

	m_pSkyBox = new cSkyBox;
	m_pSkyBox->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup("Grid", "field2.png", 160, 280, 2.0f);

	cTessadar*	m_pTessadar;
	m_pTessadar = new cTessadar;
	m_pPlayer = new cPlayer;
	m_pPlayer->SetCharacter(m_pTessadar);
	m_pPlayer->Setup();
}

void cInGame::Destroy()
{
	SAFE_DELETE(m_pLoadMap);
	SAFE_DELETE(m_pHeightMap);
	SAFE_DELETE(m_pSkyBox);

	SAFE_DELETE(m_pGrid);
	SAFE_RELEASE(m_pD3DTexture);
	XFile->Destroy();
	//m_pRootNode->Destroy();
}

void cInGame::Update()
{
	D3DXVECTOR3 pickPosition;
	for (int i = 0; i < m_pGrid->GetPicVertex().size(); i += 3)
	{
		if (Util::IntersectTri(Util::D3DXVec2TransformArray(m_ptMouse.x, m_ptMouse.y),
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
			if (Util::IntersectTri(Util::D3DXVec2TransformArray(m_ptMouse.x, m_ptMouse.y),
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

	m_pPlayer->Update();
}

void cInGame::Render()
{
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

	m_pPlayer->Render();
}



void cInGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_ptMouse.x = LOWORD(lParam);
	m_ptMouse.y = HIWORD(lParam);
}

void cInGame::SetLight()
{
	D3DLIGHT9 light;

	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 vDir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	light.Direction = vDir;
	g_pD3DDevice->SetLight(0, &light);

	g_pD3DDevice->LightEnable(0, true);

	//D3DLIGHT9 lightPoint;
	//ZeroMemory(&lightPoint, sizeof(D3DLIGHT9));
	//lightPoint.Type = D3DLIGHT_POINT;
	//lightPoint.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	//lightPoint.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	//lightPoint.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	//lightPoint.Position = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	//lightPoint.Range = 100.0f;
	//g_pD3DDevice->SetLight(1, &lightPoint);

	//g_pD3DDevice->LightEnable(1, true);

	//D3DLIGHT9 lightSpot;
	//ZeroMemory(&lightSpot, sizeof(D3DLIGHT9));
	//lightSpot.Type = D3DLIGHT_SPOT;
	//lightSpot.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	//lightSpot.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	//lightSpot.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	//lightSpot.Position = D3DXVECTOR3(0.0f, -50.0f, 0.0f);
	//lightSpot.Range = 1000.0f;
	//lightSpot.Phi = 60.0f;
	//lightSpot.Theta = 25.0f;
	//lightSpot.Falloff = 1.0f;
	////lightSpot.Attenuation0
	////lightSpot.Attenuation1

	//vDir = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//D3DXVec3Normalize(&vDir, &vDir);
	//lightSpot.Direction = vDir;
	//g_pD3DDevice->SetLight(2, &lightSpot);

	//g_pD3DDevice->LightEnable(2, true);
}
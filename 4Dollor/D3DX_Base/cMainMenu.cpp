#include "stdafx.h"
#include "cMainMenu.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cTessadar.h"
#include "cPlayer.h"
#include "cUtil.h"



cMainMenu::cMainMenu()
	: m_pGrid(NULL)
	, m_pCamera(NULL)
	, m_pD3DTexture(NULL)
{
}


cMainMenu::~cMainMenu()
{

}

void cMainMenu::SetUp()
{



	D3DXVECTOR2 temp;
	g_pTextureManager->AddTexture(L"lichKing/textures/box.png", m_pD3DTexture, &temp);

	m_pGrid = new cGrid;
	m_pGrid->Setup("Grid", "field.png", 80, 160, 1.0f);


	cTessadar*	m_pTessadar;
	m_pTessadar = new cTessadar;
	m_pPlayer = new cPlayer;
	m_pPlayer->SetCharacter(m_pTessadar);
	m_pPlayer->Setup();
}

void cMainMenu::Destroy()
{
	SAFE_DELETE(m_pGrid);
	SAFE_RELEASE(m_pD3DTexture);
	XFile->Destroy();
	//m_pRootNode->Destroy();
}

void cMainMenu::Update()
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

void cMainMenu::Render()
{
	//g_pSprite->BeginScene();
	//g_pSprite->Render(m_pD3DTexture, NULL, NULL, &D3DXVECTOR3(100, 100, 0), 255);
	//g_pSprite->End();

	if (m_pGrid)
		m_pGrid->Render();

	m_pPlayer->Render();


}

void cMainMenu::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_ptMouse.x = LOWORD(lParam);
	m_ptMouse.y = HIWORD(lParam);
}

void cMainMenu::SetLight()
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

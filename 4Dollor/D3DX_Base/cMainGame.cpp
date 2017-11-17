#include "stdafx.h"
#include "cMainGame.h"
#include "cInGame.h"



cMainGame::cMainGame()
{
}


cMainGame::~cMainGame()
{
	g_Scene->Destroy();
	g_pSprite->Destroy();
	g_pTextureManager->Destroy();
	g_pObjectManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	//cInGame* m_pGame = new cInGame;
	cMainMenu* m_pMenu = new cMainMenu;
	g_Scene->AddScene("menu", m_pMenu);
	//g_Scene->AddScene("game", m_pGame);

	cInGame* m_pInGame = new cInGame;
	g_Scene->AddScene("ingame", m_pInGame);

	g_Scene->SetUp();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void cMainGame::Update()
{
	g_pTimeManager->Update();

	g_Cam->Update();

	g_Scene->Update();


}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(155, 155, 155),
		1.0f, 0);
	g_pD3DDevice->BeginScene();

	g_Scene->Render();

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}


void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_Cam->WndProc(hWnd, message, wParam, lParam);
}
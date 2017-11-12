#include "stdafx.h"
#include "cMainGame.h"

#include "cMapTool.h"

cMainGame::cMainGame()
	: m_pMapTool(NULL)
{
}

cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pMapTool);
	
	g_pFontManager->Destroy();
	g_pTextureManager->Destroy();
	g_pObjectManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	g_cCamera->Setup();

	m_pMapTool = new cMapTool;
	m_pMapTool->Setup();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
}

void cMainGame::Update()
{
	g_pTimeManager->Update();
	g_cCamera->Update();

	if (m_pMapTool) m_pMapTool->Update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(125, 125, 125), 1.0f, 0);
	g_pD3DDevice->BeginScene();
	//===================================
	if (m_pMapTool) m_pMapTool->Render();
	//===================================
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_cCamera->WndProc(hWnd, message, wParam, lParam);

	if (m_pMapTool) m_pMapTool->ObjPicking(message, wParam, lParam);
}
#include "stdafx.h"
#include "cMainMenu.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cObjLoader.h"
#include "cGroup.h"
#include "cObjMap.h"
#include "cUIMainMenu.h"
#include "cUILoadingClientBegin.h"
#include "cUILoadingInGame.h"


cMainMenu::cMainMenu()
	: m_pGrid(NULL)
	, m_pCamera(NULL)
	, m_pD3DTexture(NULL)
	, m_pObjLoader(NULL)
	, m_pObjMap(NULL)
	, m_UI(NULL)

{
}

cMainMenu::~cMainMenu()
{
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pObjLoader);
	SAFE_DELETE(m_pObjMap);
	SAFE_RELEASE(m_pD3DTexture);


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

}

void cMainMenu::SetUp()
{
	m_UI = new cUIMainMenu;
	m_UI->setup("cMainMenu");	// ���̺� �� �з�� �̸�� ����ϹǷ� Ŭ���� �̸�� ����

	m_UILoading = new cUILoadingClientBegin;
	m_UILoading->setup("cUILoadingClientBegin");
}

void cMainMenu::Destroy()
{
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
}

void cMainMenu::Update()
{
	UpdateUI();
}

void cMainMenu::Render()
{
	RenderUI();
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


}

void cMainMenu::UpdateUI()
{
	if (m_UI && !m_UILoading)
	{
		m_UI->update();

		if (m_UI->GetGameStart())
		{
			g_Scene->ChangeScene("game");
			return;
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
}

void cMainMenu::RenderUI()
{
	if (m_UI && !m_UILoading) m_UI->renderBG();	// ��� ���� ���� ��
	else if (m_UILoading) m_UILoading->renderBG();

	if (m_UI && !m_UILoading) m_UI->render();	// ��� �� UI ��õ� ����
	else if (m_UILoading) m_UILoading->render();
}
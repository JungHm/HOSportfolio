#include "stdafx.h"
#include "cMainMenu.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cObjLoader.h"
#include "cGroup.h"
#include "cObjMap.h"
#include "cUIMainMenu.h"
#include "cUILoadingClientBegin.h"



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

<<<<<<< HEAD

	//m_pRootNode->Destroy();
=======
>>>>>>> master
}

void cMainMenu::SetUp()
{
<<<<<<< HEAD
	//// ASE Loader
	////cAseLoader	loader;
	////m_pRootNode = loader.Load("woman/woman_01_all.ASE");
	//// font
	//D3DXFONT_DESC fd;
	//ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	//fd.Height = 25;
	//fd.Width = 12;
	//fd.Weight = FW_BOLD;
	//fd.Italic = false;
	//fd.CharSet = DEFAULT_CHARSET;
	//fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	//fd.PitchAndFamily = FF_DONTCARE;

	////WCHAR str[36] = L"����ü";
	////wsprintf(str, fd.FaceName);

	////char szFaceName[32] = "����ü";
	////char* p = szFaceName;
	////strcpy_s(fd.FaceName, 32, L"����ü");

	//D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);

	//SetLight();

	
	//D3DXVECTOR2 temp;
	//g_pTextureManager->AddTexture(L"lichKing/textures/box.png", m_pD3DTexture, &temp);
	//D3DXCreateTextureFromFile(g_pD3DDevice, L"Black Dragon NEW/textures/Dragon_Bump_Col2.jpg", &m_pD3DTexture1);

=======
>>>>>>> master

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
	if (m_UI && !m_UILoading)
	{
		m_UI->update();	// ��ư�� ����Ƿ� update
		if (m_UI->GetGameStart())
		{
			g_Scene->ChangeScene("game");
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

void cMainMenu::Render()
{
	

	if (m_UI && !m_UILoading) m_UI->renderBG();	// ��� ���� ���� ��
	else if (m_UILoading) m_UILoading->renderBG();


	if (m_UI && !m_UILoading) m_UI->render();	// ��� �� UI ��õ� ����
	else if (m_UILoading) m_UILoading->render();

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
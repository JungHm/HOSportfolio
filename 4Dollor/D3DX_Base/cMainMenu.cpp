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
	//, m_pRootNode(NULL)
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


	//m_pRootNode->Destroy();
}

void cMainMenu::SetUp()
{
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
	//m_pRootNode->Update(m_pRootNode->GetKeyFrame(), NULL);
	//if (GetAsyncKeyState(VK_LBUTTON) & 0001)
	//{
	//	g_Scene->ChangeScene("game");
	//}
	if (m_UI && !m_UILoading)
	{
		m_UI->update();	// ��ư�� ����Ƿ� update
		if (m_UI->GetGameStart())
		{
			g_Scene->ChangeScene("ingame");
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
	/*RECT rc;
	SetRect(&rc, 100, 100, 200, 200);
	std::string s = "�̰��� ����ü��";
	m_pFont->DrawTextA(NULL, s.c_str(), strlen(s.c_str()), &rc,
	DT_LEFT | DT_TOP | DT_NOCLIP,
	D3DCOLOR_XRGB(255, 255, 255));

	D3DXMATRIXA16	matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, m_pD3DTexture);
	g_pD3DDevice->SetFVF(ST_PT_VERTEXT::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
	m_vecTriVertex.size() / 3,
	&m_vecTriVertex[0],
	sizeof(ST_PT_VERTEXT));*/

	if (m_UI && !m_UILoading) m_UI->renderBG();	// ��� ���� ���� ��
	else if (m_UILoading) m_UILoading->renderBG();

	//g_pSprite->BeginScene();
	//g_pSprite->Render(m_pD3DTexture, NULL, NULL, &D3DXVECTOR3(100, 100, 0), 255);
	//g_pSprite->End();

	//if (m_pRootNode)
	//	m_pRootNode->Render();

	//RenderObjFile();

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
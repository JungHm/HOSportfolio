#include "stdafx.h"
#include "cMainGame.h"

#include "cMapTool.h"
#include "cUIButton.h"
#include "cUIImageView.h"

cMainGame::cMainGame()
	: m_pMapTool(NULL)
	, m_pSprite(NULL)
	, m_pRootUI(NULL)
{
}

cMainGame::~cMainGame()
{

	SAFE_DELETE(m_pMapTool);
	
	m_pRootUI->Destroy();
	SAFE_DELETE(m_pSprite);
	
	g_pFontManager->Destroy();
	g_pTextureManager->Destroy();
	g_pObjectManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	UISetup();

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
	if (m_pRootUI) m_pRootUI->Update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	g_pD3DDevice->BeginScene();
	//===================================
	if (m_pMapTool) m_pMapTool->Render();
	if (m_pRootUI) m_pRootUI->Render(m_pSprite);
	//===================================
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::UISetup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	m_pRootUI = new cUIObject;

	cUIImageView* pImageViewCenterPanel_1 = new cUIImageView;
	pImageViewCenterPanel_1->SetTexture("MapToolUI/obj_view_panel_1.png");
	pImageViewCenterPanel_1->SetScaling(D3DXVECTOR3(1.2f, 1.2f, 1.2f));
	int nCCenter = pImageViewCenterPanel_1->GetSize().nWidth / 2;
	pImageViewCenterPanel_1->SetPosition(WINSIZEX / 2 - nCCenter, WINSIZEY - 200);
	pImageViewCenterPanel_1->SetTag(UI_IMAGE_CENTER_PANEL);
	m_pRootUI->AddChild(pImageViewCenterPanel_1);

	cUIImageView* pImageViewLeftPanel_2 = new cUIImageView;
	pImageViewLeftPanel_2->SetTexture("MapToolUI/obj_view_panel_2.png");
	pImageViewLeftPanel_2->SetScaling(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	int nLCenter = pImageViewLeftPanel_2->GetSize().nWidth / 2;
	pImageViewLeftPanel_2->SetPosition((WINSIZEX / 2 - nLCenter) - 150, WINSIZEY - 190);
	pImageViewLeftPanel_2->SetTag(UI_IMAGE_LEFT_PANEL);
	m_pRootUI->AddChild(pImageViewLeftPanel_2);

	cUIImageView* pImageViewRightPanel_2 = new cUIImageView;
	pImageViewRightPanel_2->SetTexture("MapToolUI/obj_view_panel_2.png");
	pImageViewRightPanel_2->SetScaling(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	int nRCenter = pImageViewRightPanel_2->GetSize().nWidth / 2;
	pImageViewRightPanel_2->SetPosition((WINSIZEX / 2 - nRCenter) + 175, WINSIZEY - 190);
	pImageViewRightPanel_2->SetTag(UI_IMAGE_RIGHT_PANEL);
	m_pRootUI->AddChild(pImageViewRightPanel_2);

	cUIButton* pLeftButton = new cUIButton;
	pLeftButton->SetPosition(WINSIZEX / 2 - 90, WINSIZEY - 150);
	pLeftButton->SetTexture("MapToolUI/left_normal_button.png",
		"MapToolUI/left_over_button.png",
		"MapToolUI/left_selected_button.png");
	pLeftButton->SetDelegate(this);
	pLeftButton->SetTag(UI_LEFT_BUTTON);
	m_pRootUI->AddChild(pLeftButton);

	cUIButton* pRightButton = new cUIButton;
	pRightButton->SetPosition(WINSIZEX / 2 + 80, WINSIZEY - 150);
	pRightButton->SetTexture("MapToolUI/right_normal_button.png",
		"MapToolUI/right_over_button.png",
		"MapToolUI/right_selected_button.png");
	pRightButton->SetDelegate(this);
	pRightButton->SetTag(UI_RIGHT_BUTTON);
	m_pRootUI->AddChild(pRightButton);
}

void cMainGame::OnClick(cUIButton * pSender)
{

}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_cCamera->WndProc(hWnd, message, wParam, lParam);

	if (m_pMapTool && !g_cCamera->GetButtonDown()) m_pMapTool->ObjPicking(message, wParam, lParam);
}
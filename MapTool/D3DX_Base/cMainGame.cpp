#include "stdafx.h"
#include "cMainGame.h"

#include "cMapTool.h"
#include "cUIButton.h"
#include "cSkyBox.h"

cMainGame::cMainGame()
	: m_pMapTool(NULL)
	, m_pSprite(NULL)
	, m_pRootUI(NULL)
	, m_pSkyBox(NULL)
	, m_nIndex(0)
{
	m_sUIObj[GATE_01] = "MapToolUI/Ui_Gate.png";
	m_sUIObj[WALL_01] = "MapToolUI/Ui_Wall1.png";
	m_sUIObj[WALL_02] = "MapToolUI/Ui_Wall2.png";
	m_sUIObj[WALL_03] = "MapToolUI/Ui_Wall3.png";
	m_sUIObj[WALL_04] = "MapToolUI/Ui_Wall4.png";
	m_sUIObj[WALL_05] = "MapToolUI/Ui_Wall5.png";
	m_sUIObj[FOUNTAIN] = "MapToolUI/Ui_Fountain.png";
	m_sUIObj[ROCK_00] = "MapToolUI/Ui_Rock1.png";
	m_sUIObj[ROCK_04] = "MapToolUI/Ui_Rock2.png";
	m_sUIObj[ROCK_05] = "MapToolUI/Ui_Rock3.png";
}

cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pMapTool);
	
	m_pRootUI->Destroy();
	SAFE_DELETE(m_pSprite);

	SAFE_DELETE(m_pSkyBox);
	
	g_pFontManager->Destroy();
	g_pTextureManager->Destroy();
	g_pObjectManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	g_cCamera->Setup();
	
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 vDir(0.0f, -1.0f, 0.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	light.Direction = vDir;
	g_pD3DDevice->SetLight(0, &light);
	g_pD3DDevice->LightEnable(0, true);

	UISetup();

	m_pSkyBox = new cSkyBox;
	m_pSkyBox->Setup();

	m_pMapTool = new cMapTool;
	m_pMapTool->Setup();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
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

	m_pImageCursor->SetPosition(m_nMousePos.x, m_nMousePos.y);
	cout << m_nMousePos.x << "  " << m_nMousePos.y << endl;
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(127, 127, 127), 1.0f, 0);
	g_pD3DDevice->BeginScene();
	//===================================
	if (m_pSkyBox) m_pSkyBox->Render();
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

	// 센터 패널
	cUIImageView* pImageViewCenterPanel = new cUIImageView;
	pImageViewCenterPanel->SetTexture("MapToolUI/obj_view_panel_1.png");
	pImageViewCenterPanel->SetScaling(D3DXVECTOR3(1.2f, 1.2f, 1.2f));
	int nCCenter = pImageViewCenterPanel->GetSize().nWidth / 2;
	pImageViewCenterPanel->SetPosition(WINSIZEX / 2 - nCCenter, WINSIZEY - 200);
	pImageViewCenterPanel->SetTag(UI_IMAGE_CENTER_PANEL);
	m_pRootUI->AddChild(pImageViewCenterPanel);

	// 왼쪽 패널
	cUIImageView* pImageViewLeftPanel = new cUIImageView;
	pImageViewLeftPanel->SetTexture("MapToolUI/obj_view_panel_2.png");
	pImageViewLeftPanel->SetScaling(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	int nLCenter = pImageViewLeftPanel->GetSize().nWidth / 2;
	pImageViewLeftPanel->SetPosition((WINSIZEX / 2 - nLCenter) - 150, WINSIZEY - 190);
	pImageViewLeftPanel->SetTag(UI_IMAGE_LEFT_PANEL);
	m_pRootUI->AddChild(pImageViewLeftPanel);

	// 오른쪽 패널
	cUIImageView* pImageViewRightPanel = new cUIImageView;
	pImageViewRightPanel->SetTexture("MapToolUI/obj_view_panel_2.png");
	pImageViewRightPanel->SetScaling(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	int nRCenter = pImageViewRightPanel->GetSize().nWidth / 2;
	pImageViewRightPanel->SetPosition((WINSIZEX / 2 - nRCenter) + 175, WINSIZEY - 190);
	pImageViewRightPanel->SetTag(UI_IMAGE_RIGHT_PANEL);
	m_pRootUI->AddChild(pImageViewRightPanel);

	// 왼쪽 선택 버튼
	cUIButton* pLeftButton = new cUIButton;
	pLeftButton->SetPosition(WINSIZEX / 2 - 90, WINSIZEY - 150);
	pLeftButton->SetTexture("MapToolUI/left_normal_button.png", "MapToolUI/left_over_button.png", "MapToolUI/left_selected_button.png");
	pLeftButton->SetDelegate(this);
	pLeftButton->SetTag(UI_LEFT_BUTTON);
	m_pRootUI->AddChild(pLeftButton);

	// 오른쪽 선택 버튼
	cUIButton* pRightButton = new cUIButton;
	pRightButton->SetPosition(WINSIZEX / 2 + 80, WINSIZEY - 150);
	pRightButton->SetTexture("MapToolUI/right_normal_button.png", "MapToolUI/right_over_button.png", "MapToolUI/right_selected_button.png");
	pRightButton->SetDelegate(this);
	pRightButton->SetTag(UI_RIGHT_BUTTON);
	m_pRootUI->AddChild(pRightButton);

	// 센터 오브젝트 이미지
	cUIImageView* pObjImageViewCenter = new cUIImageView;
	pObjImageViewCenter->SetTexture(m_sUIObj[GATE_01]);
	pObjImageViewCenter->SetScaling(D3DXVECTOR3(0.7f, 0.7f, 0.7f));
	pObjImageViewCenter->SetPosition(40, 40);
	pObjImageViewCenter->SetTag(UI_OBJ_IMAGE);
	pImageViewCenterPanel->AddChild(pObjImageViewCenter);

	// 왼쪽 이미지
	cUIImageView* pObjImageViewLeft = new cUIImageView;
	pObjImageViewLeft->SetTexture("MapToolUI/Ui_None.png");
	pObjImageViewLeft->SetScaling(D3DXVECTOR3(0.6f, 0.6f, 0.6f));
	pObjImageViewLeft->SetPosition(35, 35);
	pObjImageViewLeft->SetTag(UI_OBJ_IMAGE2);
	pImageViewLeftPanel->AddChild(pObjImageViewLeft);

	// 오른쪽 이미지
	cUIImageView* pObjImageViewRight = new cUIImageView;
	pObjImageViewRight->SetTexture(m_sUIObj[WALL_01]);
	pObjImageViewRight->SetScaling(D3DXVECTOR3(0.6f, 0.6f, 0.6f));
	pObjImageViewRight->SetPosition(35, 35);
	pObjImageViewRight->SetTag(UI_OBJ_IMAGE3);
	pImageViewRightPanel->AddChild(pObjImageViewRight);

	// 세이브 버튼
	cUIButton* pSaveButton = new cUIButton;
	pSaveButton->SetScaling(D3DXVECTOR3(0.7f, 0.7f, 0.7f));
	pSaveButton->SetPosition(WINSIZEX - 300, WINSIZEY - 160);
	pSaveButton->SetTexture("MapToolUI/save_normal.png", "MapToolUI/save_over.png", "MapToolUI/save_selected.png");
	pSaveButton->SetDelegate(this);
	pSaveButton->SetTag(UI_SAVE_BUTTON);
	m_pRootUI->AddChild(pSaveButton);

	// 세이브 이미지
	cUIImageView* pSaveView = new cUIImageView;
	pSaveView->SetScaling(D3DXVECTOR3(0.7f, 0.7f, 0.7f));
	pSaveView->SetTexture("MapToolUI/save.png");
	pSaveView->SetPosition(0, 0);
	pSaveView->SetTag(UI_SAVE_IMAGE);
	pSaveButton->AddChild(pSaveView);

	// 로드 버튼
	cUIButton* pLoadButton = new cUIButton;
	pLoadButton->SetScaling(D3DXVECTOR3(0.7f, 0.7f, 0.7f));
	pLoadButton->SetPosition(WINSIZEX - 200, WINSIZEY - 160);
	pLoadButton->SetTexture("MapToolUI/save_normal.png", "MapToolUI/save_over.png", "MapToolUI/save_selected.png");
	pLoadButton->SetDelegate(this);
	pLoadButton->SetTag(UI_LOAD_BUTTON);
	m_pRootUI->AddChild(pLoadButton);

	// 로드 이미지
	cUIImageView* pLoadView = new cUIImageView;
	pLoadView->SetScaling(D3DXVECTOR3(0.7f, 0.7f, 0.7f));
	pLoadView->SetTexture("MapToolUI/load.png");
	pLoadView->SetPosition(0, 0);
	pLoadView->SetTag(UI_LOAD_IMAGE);
	pLoadButton->AddChild(pLoadView);

	// 삭제 버튼
	cUIButton* pRemoveButton = new cUIButton;
	pRemoveButton->SetScaling(D3DXVECTOR3(0.7f, 0.7f, 0.7f));
	pRemoveButton->SetPosition(WINSIZEX - 400, WINSIZEY - 160);
	pRemoveButton->SetTexture("MapToolUI/save_normal.png", "MapToolUI/save_over.png", "MapToolUI/save_selected.png");
	pRemoveButton->SetDelegate(this);
	pRemoveButton->SetTag(UI_REMOVE_BUTTON);
	m_pRootUI->AddChild(pRemoveButton);

	// 삭제 이미지
	cUIImageView* pRemoveView = new cUIImageView;
	pRemoveView->SetScaling(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	pRemoveView->SetTexture("MapToolUI/remove.png");
	pRemoveView->SetPosition(10, 10);
	pRemoveView->SetTag(UI_REMOVE_IMAGE);
	pRemoveButton->AddChild(pRemoveView);

	// 마우스 커서 이미지
	m_pImageCursor = new cUIImageView;
	m_pImageCursor->SetTexture("MapToolUI/Cursor.png");
	m_pImageCursor->SetPosition(m_nMousePos.x, m_nMousePos.y);
	m_pRootUI->AddChild(m_pImageCursor);
}

void cMainGame::OnClick(cUIButton * pSender)
{
	cUIImageView* pCenter = (cUIImageView*)m_pRootUI->FindChildByTag(UI_OBJ_IMAGE);
	cUIImageView* pLeft = (cUIImageView*)m_pRootUI->FindChildByTag(UI_OBJ_IMAGE2);
	cUIImageView* pRight = (cUIImageView*)m_pRootUI->FindChildByTag(UI_OBJ_IMAGE3);

	switch (pSender->GetTag())
	{
	case UI_LEFT_BUTTON:
		if (m_nIndex == 9) return;
		m_nIndex++;
		break;

	case UI_RIGHT_BUTTON:
		if (m_nIndex == 0) return;
		m_nIndex--;
		break;

	case UI_SAVE_BUTTON:
		m_pMapTool->ObjSave();
		break;

	case UI_LOAD_BUTTON:
		m_pMapTool->ObjLoad();
		break;

	case UI_REMOVE_BUTTON:
		m_pMapTool->ObjRemove();
		break;
	}

	pLeft->SetTexture(m_sUIObj[m_nIndex - 1]);
	pCenter->SetTexture(m_sUIObj[m_nIndex]);
	if (m_nIndex < 9) pRight->SetTexture(m_sUIObj[m_nIndex + 1]);	
	if (m_nIndex == 9) pRight->SetTexture("MapToolUI/Ui_None.png");
	
	m_pMapTool->SetIndex(m_nIndex);		// 맵툴에서 현재 선택되는 오브젝트를 바꿔준다
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_cCamera->WndProc(hWnd, message, wParam, lParam);

	m_nMousePos.x = LOWORD(lParam);
	m_nMousePos.y = HIWORD(lParam);

	if (m_pMapTool && !g_cCamera->GetButtonDown()) m_pMapTool->ObjPicking(message, wParam, lParam);
}
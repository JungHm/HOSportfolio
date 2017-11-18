#include "stdafx.h"
#include "cMapTool.h"
#include "cGrid.h"
#include "cInfomation.h"
#include "cPicking.h"
#include "cSaveLoad.h"
#include "cHeightMap.h"

cMapTool::cMapTool()
	: m_pGrid(NULL)
	, m_pInfo(NULL)
	, m_pHeightMap(NULL)
	, m_isPicking(false)
	, m_isAllocate(true)
{
}

cMapTool::~cMapTool()
{	
	SAFE_RELEASE(m_sObj.pMesh);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pInfo);
	SAFE_DELETE(m_pHeightMap);
	SAFE_DELETE(m_pSaveLoad);
}

void cMapTool::SetUpPickingObj()
{
	ZeroMemory(&m_sObj, sizeof(OBJECT));

	D3DXMatrixIdentity(&m_sObj.matWorld);
	D3DXMatrixIdentity(&m_sObj.matScal);
	D3DXMatrixIdentity(&m_sObj.matRotY);
	D3DXMatrixIdentity(&m_sObj.matTrans);

	m_sObj.vScaling = D3DXVECTOR3(0.03f, 0.03f, 0.03f);
}

void cMapTool::Setup()
{
	SetUpPickingObj();

	m_pHeightMap = new cHeightMap;
	m_pHeightMap->Setup("HeightMap/", "backGround.raw", "HeightMap.jpg");

	m_pSaveLoad = new cSaveLoad;

	m_pInfo = new cInfomation;
	m_pInfo->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup("Grid", "field2.png", 160, 280, 2.0f);

	m_sObj.pMesh = m_pSaveLoad->GetObjMesh(m_nIndex);
	m_sObj.nKind = m_nIndex;

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TFACTOR);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void cMapTool::Update()
{
	if (KEY->isOnceKeyDown(VK_LBUTTON))
		m_pSaveLoad->CreateObj(
			m_nIndex,
			m_sObj.pMesh,
			m_pSaveLoad->GetMapObjMtltex(m_nIndex),
			m_pSaveLoad->GetFileName(m_nIndex),
			m_sObj.vScaling, m_sObj.vPosition,
			m_sObj.fAngleY);

	m_pInfo->SetScale(m_sObj.vScaling.x);
	m_pInfo->SetRotation(m_sObj.fAngleY);
	m_pInfo->SetPosition(m_sObj.vPosition);
	m_pInfo->SetObjKind(m_sObj.nKind);
	m_pInfo->SetObjNum(m_pSaveLoad->GetFieldObjNum());
}

void cMapTool::Render()
{
	if (m_pInfo) m_pInfo->Render();
	if (m_pGrid) m_pGrid->Render();
	if (m_pSaveLoad) m_pSaveLoad->CreateObjRender();
	if (m_pHeightMap) m_pHeightMap->Render();
	
	if (m_isAllocate)
	{
		D3DXMatrixScaling(&m_sObj.matScal, m_sObj.vScaling.x, m_sObj.vScaling.y, m_sObj.vScaling.z);
		D3DXMatrixRotationY(&m_sObj.matRotY, m_sObj.fAngleY);
		D3DXMatrixTranslation(&m_sObj.matTrans, m_sObj.vPosition.x, m_sObj.vPosition.y, m_sObj.vPosition.z);

		m_sObj.matWorld = m_sObj.matScal * m_sObj.matRotY * m_sObj.matTrans;

		g_pD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(130, 255, 255, 255));
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_sObj.matWorld);

		for (size_t i = 0; i < m_pSaveLoad->GetMapObjMtltex(m_nIndex).size(); i++)
		{
			g_pD3DDevice->SetMaterial(&m_pSaveLoad->GetMapObjMtltex(m_nIndex)[i]->GetMaterial());
			g_pD3DDevice->SetTexture(0, m_pSaveLoad->GetMapObjMtltex(m_nIndex)[i]->GetTexture());
			m_sObj.pMesh->DrawSubset(i);
		}
	}
}

void cMapTool::ObjPicking(IN UINT message, IN WPARAM wParam, IN LPARAM lParam)
{
	cPicking cRay = cPicking::CalcWorldSpace(LOWORD(lParam), HIWORD(lParam));
	D3DXVECTOR3 vOutPos;

	switch (message)
	{
	case WM_MOUSEMOVE:
		if (m_isAllocate)
		{
			for (int i = 0; i < m_pGrid->GetPicVertex().size(); i += 3)
			{
				m_isPicking = cRay.IntersectTri(
					m_pGrid->GetPicVertex()[i].p,
					m_pGrid->GetPicVertex()[i + 1].p,
					m_pGrid->GetPicVertex()[i + 2].p,
					vOutPos);

				if (m_isPicking)
				{
					m_sObj.vPosition = vOutPos;
					break;
				}
			}
		}
		break;

	case WM_MOUSEWHEEL:
		if (KEY->isStayKeyDown('R'))
		{
			m_sObj.vScaling.x += (GET_WHEEL_DELTA_WPARAM(wParam) / 30000.f);
			m_sObj.vScaling.y += (GET_WHEEL_DELTA_WPARAM(wParam) / 30000.f);
			m_sObj.vScaling.z += (GET_WHEEL_DELTA_WPARAM(wParam) / 30000.f);
		}
		break;
	}

	if (KEY->isOnceKeyDown('Q')) m_sObj.fAngleY -= D3DX_PI / 18;
	if (KEY->isOnceKeyDown('E')) m_sObj.fAngleY += D3DX_PI / 18;

	m_sObj.pMesh = m_pSaveLoad->GetObjMesh(m_nIndex);
	m_sObj.nKind = m_nIndex;
}

void cMapTool::ObjSave()
{
	m_pSaveLoad->SaveFieldObj();
}

void cMapTool::ObjLoad()
{
	m_pSaveLoad->LoadFieldObj();
}

void cMapTool::ObjRemove()
{
	m_pSaveLoad->RemoveObj();
}

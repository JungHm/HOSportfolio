#include "stdafx.h"
#include "cMapTool.h"

#include "cGrid.h"
#include "cInfomation.h"
#include "cObjLoader.h"
#include "cMtlTex.h"
#include "cPicking.h"
#include "cSaveLoad.h"

cMapTool::cMapTool()
	: m_pGrid(NULL)
	, m_pInfo(NULL)
	, m_pObjLoader(NULL)
	, m_isPicking(false)
	, m_isAllocate(false)
{
	m_sFileName[GATE] = "Storm_Building_WinterCrest_Gate_00_Sc2.obj";
	m_sFileName[WELL] = "Storm_Building_KingsCrest_ManaWell_Sc2.obj";
	m_sFileName[FOUNTAIN] = "Storm_Doodad_KingsCrest_Fountain_00.obj";
}

cMapTool::~cMapTool()
{	
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pInfo);
	SAFE_DELETE(m_pObjLoader);
	SAFE_DELETE(m_pSaveLoad);
	SAFE_RELEASE(m_sObj.pMesh);
	
	for (int i = 0; i < OBJNUM; i++)
	{
		//SAFE_RELEASE(m_pObjMesh[i]);
	}
}

void cMapTool::SetUpObj()
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
	SetUpObj();

	m_pInfo = new cInfomation;
	m_pInfo->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup("Grid", "field.png", 80, 160, 1.0f);

	m_pObjLoader = new cObjLoader;
	m_pObjMesh[GATE] = m_pObjLoader->LoadMesh(m_mapObjMtlTex[GATE], "obj", m_sFileName[GATE]);
	m_pObjMesh[WELL] = m_pObjLoader->LoadMesh(m_mapObjMtlTex[WELL], "obj", m_sFileName[WELL]);
	m_pObjMesh[FOUNTAIN] = m_pObjLoader->LoadMesh(m_mapObjMtlTex[FOUNTAIN], "obj", m_sFileName[FOUNTAIN]);
	
	m_pSaveLoad = new cSaveLoad;
	
	m_sObj.pMesh = m_pObjMesh[m_nIndex];

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TFACTOR);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void cMapTool::Update()
{
	ObjSelect();
}

void cMapTool::Render()
{
	if (m_pInfo) m_pInfo->Render();
	if (m_pGrid) m_pGrid->Render();
	if (m_pSaveLoad) m_pSaveLoad->CreateObjRender();

	D3DXMatrixScaling(&m_sObj.matScal, m_sObj.vScaling.x, m_sObj.vScaling.y, m_sObj.vScaling.z);
	D3DXMatrixRotationY(&m_sObj.matRotY, m_sObj.fAngleY);
	D3DXMatrixTranslation(&m_sObj.matTrans, m_sObj.vPosition.x, m_sObj.vPosition.y, m_sObj.vPosition.z);

	m_sObj.matWorld = m_sObj.matScal * m_sObj.matRotY * m_sObj.matTrans;

	g_pD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(60, 255, 255, 255));
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_sObj.matWorld);

	for (size_t i = 0; i < m_mapObjMtlTex[m_nIndex].size(); i++)
	{
		g_pD3DDevice->SetMaterial(&m_mapObjMtlTex[m_nIndex][i]->GetMaterial());
		g_pD3DDevice->SetTexture(0, m_mapObjMtlTex[m_nIndex][i]->GetTexture());
		m_sObj.pMesh->DrawSubset(i);
	}
}

void cMapTool::ObjPicking(IN UINT message, IN WPARAM wParam, IN LPARAM lParam)
{
	cPicking cRay = cPicking::CalcWorldSpace(LOWORD(lParam), HIWORD(lParam));
	D3DXVECTOR3 vOutPos;

	switch (message)
	{
	case WM_MOUSEMOVE:
		if (!m_isAllocate)
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
			m_sObj.vScaling.x += (GET_WHEEL_DELTA_WPARAM(wParam) / 100000.f);
			m_sObj.vScaling.y += (GET_WHEEL_DELTA_WPARAM(wParam) / 100000.f);
			m_sObj.vScaling.z += (GET_WHEEL_DELTA_WPARAM(wParam) / 100000.f);
		}
		break;
	}

	if (KEY->isOnceKeyDown(VK_LBUTTON))
	{
		m_pSaveLoad->CreateObj(m_sObj.pMesh, m_mapObjMtlTex[m_nIndex], m_sFileName[m_nIndex], m_sObj.vScaling, m_sObj.vPosition, m_sObj.fAngleY);
	}
}

void cMapTool::ObjSelect()
{
	if (KEY->isOnceKeyDown('Q')) m_sObj.fAngleY -= D3DX_PI / 4;
	if (KEY->isOnceKeyDown('E')) m_sObj.fAngleY += D3DX_PI / 4;

	if (KEY->isOnceKeyDown('X'))
	{
		if (m_nIndex == 0) return;
		m_nIndex--;
	}

	if (KEY->isOnceKeyDown('C'))
	{
		if (m_nIndex == OBJNUM - 1) return;
		m_nIndex++;
	}

	m_sObj.pMesh = m_pObjMesh[m_nIndex];
}


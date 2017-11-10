#include "stdafx.h"
#include "cMapTool.h"

#include "cGrid.h"
#include "cInfomation.h"
#include "cObjLoader.h"
#include "cMtlTex.h"
#include "cPicking.h"

cMapTool::cMapTool()
	: m_pGrid(NULL)
	, m_pInfo(NULL)
	, m_pObjLoader(NULL)
	, m_vObjPos(0.0f, 0.0f, 0.0f)
	, m_isPicking(false)
{
}

cMapTool::~cMapTool()
{	
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pInfo);
	SAFE_RELEASE(m_pObjMesh);
	SAFE_DELETE(m_pObjLoader);
}

void cMapTool::ObjLoaderTestSetup()
{
	m_pInfo = new cInfomation;
	m_pInfo->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup("Grid", "field.png", 80, 160, 1.0f);

	m_pObjLoader = new cObjLoader;
	m_pObjMesh = m_pObjLoader->LoadMesh(m_vecObjMtlTex, "obj", "Storm_Building_WinterCrest_Gate_00_Sc2.obj");
}

void cMapTool::ObjLoaderTestRender()
{
	if (m_pInfo) m_pInfo->Render();
	if (m_pGrid) m_pGrid->Render();

	D3DXMATRIXA16 matWorld, matS, matR, matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matS, 0.03f, 0.03f, 0.03f);
	D3DXMatrixTranslation(&matT, m_vObjPos.x, m_vObjPos.y, m_vObjPos.z);
	
	cout << "X : " << m_vObjPos.x << " Y : " << m_vObjPos.y << " Z : " << m_vObjPos.z << endl;

	matWorld = matS * matT;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	for (size_t i = 0; i < m_vecObjMtlTex.size(); i++)
	{
		g_pD3DDevice->SetMaterial(&m_vecObjMtlTex[i]->GetMaterial());
		g_pD3DDevice->SetTexture(0, m_vecObjMtlTex[i]->GetTexture());
		m_pObjMesh->DrawSubset(i);
	}
}

void cMapTool::ObjPicking(LPARAM lParam)
{
	cPicking cRay = cPicking::CalcWorldSpace(LOWORD(lParam), HIWORD(lParam));
	D3DXVECTOR3 vOutPos;

	for (int i = 0; i < m_pGrid->GetPicVertex().size(); i += 3)
	{
		m_isPicking = cRay.IntersectTri(m_pGrid->GetPicVertex()[i].p, m_pGrid->GetPicVertex()[i + 1].p, m_pGrid->GetPicVertex()[i + 2].p, vOutPos);

		if (m_isPicking)
		{
			m_vObjPos = vOutPos;
			break;
		}
	}
}

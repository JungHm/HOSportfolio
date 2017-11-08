#include "stdafx.h"
#include "cMapTool.h"

#include "cGrid.h"
#include "cObjLoader.h"
#include "cMtlTex.h"

cMapTool::cMapTool()
	: m_pGrid(NULL)
	, m_pObjLoader(NULL)
{
}

cMapTool::~cMapTool()
{	
	SAFE_DELETE(m_pGrid);
	SAFE_RELEASE(m_pObjMesh);
	SAFE_DELETE(m_pObjLoader);
}

void cMapTool::ObjLoaderTestSetup()
{
	m_pGrid = new cGrid;
	m_pGrid->Setup("Grid", "field.png", 80, 160, 1.0f);

	m_pObjLoader = new cObjLoader;
	m_pObjMesh = m_pObjLoader->LoadMesh(m_vecObjMtlTex, "obj", "Storm_Building_WinterCrest_Gate_00_Sc2.obj");
}

void cMapTool::ObjLoaderTestRender()
{
	if (m_pGrid) m_pGrid->Render();

	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matS, 0.03f, 0.03f, 0.03f);
	
	matWorld = matS;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	for (size_t i = 0; i < m_vecObjMtlTex.size(); i++)
	{
		g_pD3DDevice->SetMaterial(&m_vecObjMtlTex[i]->GetMaterial());
		g_pD3DDevice->SetTexture(0, m_vecObjMtlTex[i]->GetTexture());
		m_pObjMesh->DrawSubset(i);
	}
}

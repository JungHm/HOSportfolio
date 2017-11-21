#include "stdafx.h"
#include "cSkyBox.h"
#include "cObjLoader.h"

cSkyBox::cSkyBox()
	: m_pObjLoader(NULL)
	, m_pMesh(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cSkyBox::~cSkyBox()
{
	SAFE_DELETE(m_pObjLoader);
	SAFE_RELEASE(m_pMesh);
}

void cSkyBox::Setup()
{
	m_pObjLoader = new cObjLoader;
	m_pMesh = m_pObjLoader->LoadMesh(m_vecMtlTex, "Skybox", "skybox.obj");
}

void cSkyBox::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	D3DXMATRIXA16 matS, matT;
	D3DXMatrixScaling(&matS, 0.3f, 0.3f, 0.3f);
	D3DXMatrixTranslation(&matT, 0.0f, 100.0f, 100.0f);

	m_matWorld = matS * matT;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	for (size_t i = 0; i < m_vecMtlTex.size(); i++)
	{
		g_pD3DDevice->SetMaterial(&m_vecMtlTex[i]->GetMaterial());
		g_pD3DDevice->SetTexture(0, m_vecMtlTex[i]->GetTexture());
		m_pMesh->DrawSubset(i);
	}
}

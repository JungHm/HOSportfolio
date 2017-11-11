#include "stdafx.h"
#include "cSaveLoad.h"

cSaveLoad::cSaveLoad()
{
}

cSaveLoad::~cSaveLoad()
{
	for (int i = 0; i < m_vecFieldObj.size(); i++)
	{
		//SAFE_RELEASE(m_vecFieldObj[i].pMesh);
	}
}

void cSaveLoad::CreateObj(IN LPD3DXMESH pMesh, IN vector<cMtlTex*> vecValue, IN string sFileName, IN D3DXVECTOR3 vScal, IN D3DXVECTOR3 vPos, IN float fAngleY)
{
	OBJECT obj;
	ZeroMemory(&obj, sizeof(OBJECT));

	D3DXMatrixIdentity(&obj.matWorld);
	D3DXMatrixIdentity(&obj.matScal);
	D3DXMatrixIdentity(&obj.matRotY);
	D3DXMatrixIdentity(&obj.matTrans);

	obj.pMesh = pMesh;
	obj.vecMtlTex = vecValue;
	obj.sFileName = sFileName;
	obj.vScaling = vScal;
	obj.vPosition = vPos;
	obj.fAngleY = fAngleY;

	m_vecFieldObj.push_back(obj);
}

void cSaveLoad::CreateObjRender()
{
	g_pD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	for (int i = 0; i < m_vecFieldObj.size(); i++)
	{
		if (m_vecFieldObj.size() == NULL) return;

		D3DXMatrixScaling(&m_vecFieldObj[i].matScal, m_vecFieldObj[i].vScaling.x, m_vecFieldObj[i].vScaling.y, m_vecFieldObj[i].vScaling.z);
		D3DXMatrixRotationY(&m_vecFieldObj[i].matRotY, m_vecFieldObj[i].fAngleY);
		D3DXMatrixTranslation(&m_vecFieldObj[i].matTrans, m_vecFieldObj[i].vPosition.x, m_vecFieldObj[i].vPosition.y, m_vecFieldObj[i].vPosition.z);

		m_vecFieldObj[i].matWorld = m_vecFieldObj[i].matScal * m_vecFieldObj[i].matRotY * m_vecFieldObj[i].matTrans;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_vecFieldObj[i].matWorld);

		for (size_t j = 0; j < m_vecFieldObj[i].vecMtlTex.size(); j++)
		{
			g_pD3DDevice->SetMaterial(&m_vecFieldObj[i].vecMtlTex[j]->GetMaterial());
			g_pD3DDevice->SetTexture(0, m_vecFieldObj[i].vecMtlTex[j]->GetTexture());
			m_vecFieldObj[i].pMesh->DrawSubset(j);
		}
	}
}

void cSaveLoad::Save()
{

}

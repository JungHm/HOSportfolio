#include "stdafx.h"
#include "cSaveLoad.h"
#include "cObjLoader.h"

cSaveLoad::cSaveLoad()
	: m_pObjLoader(NULL)
{
	m_sFileName[GATE] = "Storm_Building_WinterCrest_Gate_00_Sc2.obj";
	m_sFileName[WELL] = "Storm_Building_KingsCrest_ManaWell_Sc2.obj";
	m_sFileName[FOUNTAIN] = "Storm_Doodad_KingsCrest_Fountain_00.obj";

	m_pObjLoader = new cObjLoader;
	m_pObjMesh[GATE] = m_pObjLoader->LoadMesh(m_mapObjMtlTex[GATE], "obj", m_sFileName[GATE]);
	m_pObjMesh[WELL] = m_pObjLoader->LoadMesh(m_mapObjMtlTex[WELL], "obj", m_sFileName[WELL]);
	m_pObjMesh[FOUNTAIN] = m_pObjLoader->LoadMesh(m_mapObjMtlTex[FOUNTAIN], "obj", m_sFileName[FOUNTAIN]);
}

cSaveLoad::~cSaveLoad()
{
	SAFE_DELETE(m_pObjLoader);

	for (int i = 0; i < OBJNUM; i++)
	{
		SAFE_RELEASE(m_pObjMesh[i]);
	}

	for (unsigned int i = 0; i < m_vecFieldObj.size(); i++)
	{
		SAFE_RELEASE(m_vecFieldObj[i].pMesh);
	}
}

void cSaveLoad::CreateObj(IN int nKind, IN LPD3DXMESH pMesh, IN vector<cMtlTex*> vecValue, IN string sFileName, IN D3DXVECTOR3 vScal, IN D3DXVECTOR3 vPos, IN float fAngleY)
{
	OBJECT obj;
	ZeroMemory(&obj, sizeof(OBJECT));

	D3DXMatrixIdentity(&obj.matWorld);
	D3DXMatrixIdentity(&obj.matScal);
	D3DXMatrixIdentity(&obj.matRotY);
	D3DXMatrixIdentity(&obj.matTrans);

	obj.nKind = nKind;
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
	if (m_vecFieldObj.size() == NULL) return;
	
	g_pD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	for (unsigned int i = 0; i < m_vecFieldObj.size(); i++)
	{
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

void cSaveLoad::RemoveObj()
{
	if (m_vecFieldObj.size() == NULL) return;

	m_vecFieldObj.pop_back();
}

void cSaveLoad::SaveFieldObj()
{
	if (m_vecFieldObj.size() == NULL) return;

	FILE* fp;
	fopen_s(&fp, "SaveFieldObj/FieldObj.txt", "w");

	for (unsigned int i = 0; i < m_vecFieldObj.size(); i++)
	{
		fprintf(fp, "%d ", m_vecFieldObj[i].nKind);																			// 파일 종류
		fprintf(fp, "%f %f %f ", m_vecFieldObj[i].vPosition.x, m_vecFieldObj[i].vPosition.y, m_vecFieldObj[i].vPosition.z); // 위치 좌표
		fprintf(fp, "%f %f %f ", m_vecFieldObj[i].vScaling.x, m_vecFieldObj[i].vScaling.y, m_vecFieldObj[i].vScaling.z);	// 크기
		fprintf(fp, "%f\n", m_vecFieldObj[i].fAngleY);																		// y축 회전 값
	}

	fclose(fp);
}

void cSaveLoad::LoadFieldObj()
{
	m_vecFieldObj.clear();

	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vScal;
	int			nKind;
	float		fAngleY;

	FILE* fp;
	fopen_s(&fp, "SaveFieldObj/FieldObj.txt", "r");

	while (true)
	{
		if (feof(fp)) break;

		fscanf_s(fp, "%d %f %f %f %f %f %f %f",
			&nKind,
			&vPos.x, &vPos.y, &vPos.z,
			&vScal.x, &vScal.y, &vScal.z,
			&fAngleY);

		CreateObj(nKind, m_pObjMesh[nKind], m_mapObjMtlTex[nKind], m_sFileName[nKind], vScal, vPos, fAngleY);
	}

	fclose(fp);
}

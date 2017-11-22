#include "stdafx.h"
#include "cSaveLoad.h"
#include "cObjLoader.h"

cSaveLoad::cSaveLoad()
	: m_pObjLoader(NULL)
{
	// 원하는 obj파일 지정
	m_sFileName[GATE_01] = "Gate_01.obj";
	m_sFileName[WALL_01] = "Wall_01.obj";
	m_sFileName[WALL_02] = "Wall_02.obj";
	m_sFileName[WALL_03] = "Wall_03.obj";
	m_sFileName[WALL_04] = "Wall_04.obj";
	m_sFileName[WALL_05] = "Wall_05.obj";	
	m_sFileName[FOUNTAIN] = "Storm_Doodad_KingsCrest_Fountain_00.obj";	
	m_sFileName[ROCK_00] = "Storm_Doodad_KingsCrest_BigChunkyRock_00_Sc2.obj";
	m_sFileName[ROCK_04] = "Storm_Doodad_KingsCrest_BigChunkyRock_04_Sc2.obj";
	m_sFileName[ROCK_05] = "Storm_Doodad_KingsCrest_BigChunkyRock_05_Sc2.obj";

	// 지정한 obj파일 매쉬 생성 후 저장
	m_pObjLoader = new cObjLoader;
	m_pObjMesh[GATE_01] = m_pObjLoader->LoadMesh(m_mapObjMtlTex[GATE_01], "obj", m_sFileName[GATE_01]);
	m_pObjMesh[WALL_01] = m_pObjLoader->LoadMesh(m_mapObjMtlTex[WALL_01], "obj", m_sFileName[WALL_01]);
	m_pObjMesh[WALL_02] = m_pObjLoader->LoadMesh(m_mapObjMtlTex[WALL_02], "obj", m_sFileName[WALL_02]);
	m_pObjMesh[WALL_03] = m_pObjLoader->LoadMesh(m_mapObjMtlTex[WALL_03], "obj", m_sFileName[WALL_03]);
	m_pObjMesh[WALL_04] = m_pObjLoader->LoadMesh(m_mapObjMtlTex[WALL_04], "obj", m_sFileName[WALL_04]);
	m_pObjMesh[WALL_05] = m_pObjLoader->LoadMesh(m_mapObjMtlTex[WALL_05], "obj", m_sFileName[WALL_05]);	
	m_pObjMesh[FOUNTAIN] = m_pObjLoader->LoadMesh(m_mapObjMtlTex[FOUNTAIN], "obj", m_sFileName[FOUNTAIN]);	
	m_pObjMesh[ROCK_00] = m_pObjLoader->LoadMesh(m_mapObjMtlTex[ROCK_00], "obj", m_sFileName[ROCK_00]);
	m_pObjMesh[ROCK_04] = m_pObjLoader->LoadMesh(m_mapObjMtlTex[ROCK_04], "obj", m_sFileName[ROCK_04]);
	m_pObjMesh[ROCK_05] = m_pObjLoader->LoadMesh(m_mapObjMtlTex[ROCK_05], "obj", m_sFileName[ROCK_05]);

	// 노드 선택 메터리얼 초기화
	ZeroMemory(&m_mtlNone, sizeof(D3DMATERIAL9));
	m_mtlNone.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_mtlNone.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_mtlNone.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	ZeroMemory(&m_mtlSelected, sizeof(D3DMATERIAL9));
	m_mtlSelected.Ambient = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	m_mtlSelected.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	m_mtlSelected.Specular = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
}

cSaveLoad::~cSaveLoad()
{
	for (unsigned int i = 0; i < m_vecFieldObj.size(); i++)
	{
		SAFE_RELEASE(m_vecFieldObj[i].pMesh);
	}

	for (int i = 0; i < OBJNUM; i++)
	{
		SAFE_RELEASE(m_pObjMesh[i]);
	}

	SAFE_DELETE(m_pObjLoader);
}

void cSaveLoad::CreateBox(IN LPD3DXMESH pMesh, IN D3DXVECTOR3 vScal, IN D3DXVECTOR3 vPos, IN float fAngleY)
{
	ST_BOX box;
	ZeroMemory(&box, sizeof(ST_BOX));

	D3DXMatrixIdentity(&box.matWorld);
	D3DXMatrixIdentity(&box.matScal);
	D3DXMatrixIdentity(&box.matRotY);
	D3DXMatrixIdentity(&box.matTrans);

	box.pMesh = pMesh;
	box.vScaling = vScal;
	box.vPosition = vPos;
	box.fAngleY = fAngleY;

	D3DXCreateBox(g_pD3DDevice, 30.0f, 20.0f, 13.0f, &box.pMesh, NULL);

	m_vecFieldBox.push_back(box);
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

void cSaveLoad::CreateNodeSphere(IN LPD3DXMESH pMesh, IN D3DXVECTOR3 vPos, IN vector<NODE> vecNode)
{
	ST_SPHERE sphere;
	ZeroMemory(&sphere, sizeof(ST_SPHERE));

	D3DXMatrixIdentity(&sphere.matWrold);
	D3DXMatrixIdentity(&sphere.matTrans);

	sphere.pMesh = pMesh;
	sphere.vCenter = vPos;
	sphere.isVisit = false;
	
	if (vecNode.size() != NULL)
	{
		sphere.vecLink.resize(vecNode.size());

		for (int i = 0; i < sphere.vecLink.size(); i++)
		{
			sphere.vecLink[i].nIndex = vecNode[i].nIndex;
			sphere.vecLink[i].fCost = vecNode[i].fCost;
		}
	}

	D3DXCreateSphere(g_pD3DDevice, 2.5f, 15, 15, &sphere.pMesh, NULL);

	m_vecFieldNodeSphere.push_back(sphere);
}

void cSaveLoad::CostSetup(IN int nSize)
{
	m_vecCost.resize(nSize);

	for (int i = 0; i < m_vecCost.size(); i++)
	{
		m_vecCost[i].fCost = INF;
		m_vecCost[i].nViaIndex = 0;
	}
}

void cSaveLoad::CreateObjRender()
{
	g_pD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	// 배치된 오브젝트 렌더
	for (unsigned int i = 0; i < m_vecFieldObj.size(); i++)
	{
		D3DXMatrixScaling(&m_vecFieldObj[i].matScal, m_vecFieldObj[i].vScaling.x, m_vecFieldObj[i].vScaling.y, m_vecFieldObj[i].vScaling.z);
		D3DXMatrixRotationY(&m_vecFieldObj[i].matRotY, m_vecFieldObj[i].fAngleY);
		D3DXMatrixTranslation(&m_vecFieldObj[i].matTrans, m_vecFieldObj[i].vPosition.x, m_vecFieldObj[i].vPosition.y, m_vecFieldObj[i].vPosition.z);

		m_vecFieldObj[i].matWorld = m_vecFieldObj[i].matScal * m_vecFieldObj[i].matRotY * m_vecFieldObj[i].matTrans;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_vecFieldObj[i].matWorld);
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		for (size_t j = 0; j < m_vecFieldObj[i].vecMtlTex.size(); j++)
		{
			g_pD3DDevice->SetMaterial(&m_vecFieldObj[i].vecMtlTex[j]->GetMaterial());
			g_pD3DDevice->SetTexture(0, m_vecFieldObj[i].vecMtlTex[j]->GetTexture());
			m_vecFieldObj[i].pMesh->DrawSubset(j);
		}
	}
	
	// 배치된 충돌 박스 렌더
	for (unsigned int i = 0; i < m_vecFieldBox.size(); i++)
	{
		D3DXMatrixScaling(&m_vecFieldBox[i].matScal, m_vecFieldBox[i].vScaling.x, m_vecFieldBox[i].vScaling.y, m_vecFieldBox[i].vScaling.z);
		D3DXMatrixRotationY(&m_vecFieldBox[i].matRotY, m_vecFieldBox[i].fAngleY);
		D3DXMatrixTranslation(&m_vecFieldBox[i].matTrans, m_vecFieldBox[i].vPosition.x, m_vecFieldBox[i].vPosition.y, m_vecFieldBox[i].vPosition.z);

		m_vecFieldBox[i].matWorld = m_vecFieldBox[i].matScal * m_vecFieldBox[i].matRotY * m_vecFieldBox[i].matTrans;
		
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_vecFieldBox[i].matWorld);
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		g_pD3DDevice->SetTexture(0, NULL);
		
		m_vecFieldBox[i].pMesh->DrawSubset(0);
	}
	
	// 노드 간의 라인 렌더
	if (m_vecNodeLine.size() % 2 == 0 && m_vecNodeLine.size() != NULL)
	{
		D3DXMATRIXA16 matWorld, matT;
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixTranslation(&matT, 0.0f, 0.1f, 0.0f);

		matWorld = matT;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetFVF(ST_PC_VERTEXT::FVF);
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		g_pD3DDevice->SetTexture(0, NULL);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecNodeLine.size() / 2, &m_vecNodeLine[0], sizeof(ST_PC_VERTEXT));
	}

	// 배치된 노드 렌더
	for (unsigned int i = 0; i < m_vecFieldNodeSphere.size(); i++)
	{
		D3DXMatrixTranslation(&m_vecFieldNodeSphere[i].matTrans, m_vecFieldNodeSphere[i].vCenter.x, m_vecFieldNodeSphere[i].vCenter.y, m_vecFieldNodeSphere[i].vCenter.z);

		m_vecFieldNodeSphere[i].matWrold = m_vecFieldNodeSphere[i].matTrans;
		
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_vecFieldNodeSphere[i].matWrold);
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		g_pD3DDevice->SetMaterial(m_vecFieldNodeSphere[i].isSelected ? &m_mtlSelected : &m_mtlNone);
		g_pD3DDevice->SetTexture(0, NULL);

		m_vecFieldNodeSphere[i].pMesh->DrawSubset(0);
	}
}

void cSaveLoad::RemoveObj()
{
	if (m_vecFieldObj.size() == NULL) return;
	m_vecFieldObj.pop_back();
}

void cSaveLoad::RemoveBox()
{
	if (m_vecFieldBox.size() == NULL) return;
	m_vecFieldBox.pop_back();
}

void cSaveLoad::RemoveNode()
{
	if (m_vecFieldNodeSphere.size() == NULL) return;
	m_vecFieldNodeSphere.pop_back();
}

void cSaveLoad::SaveFieldObj()
{
	FILE* fp = NULL;

	if (m_vecFieldObj.size() == NULL) return;
	// 오브젝트 파일 세이브
	fopen_s(&fp, "SaveFieldObj/FieldObj.txt", "w");
	for (unsigned int i = 0; i < m_vecFieldObj.size(); i++)
	{
		fprintf(fp, "%d ", m_vecFieldObj[i].nKind);																			
		fprintf(fp, "%f %f %f ", m_vecFieldObj[i].vPosition.x, m_vecFieldObj[i].vPosition.y, m_vecFieldObj[i].vPosition.z); 
		fprintf(fp, "%f %f %f ", m_vecFieldObj[i].vScaling.x, m_vecFieldObj[i].vScaling.y, m_vecFieldObj[i].vScaling.z);	
		fprintf(fp, "%f\n", m_vecFieldObj[i].fAngleY);																		
	}
	fclose(fp);

	if (m_vecFieldBox.size() == NULL) return;
	// 충돌 박스 세이브
	fopen_s(&fp, "SaveFieldCollisionBox/FieldBox.txt", "w");
	for (unsigned int i = 0; i < m_vecFieldBox.size(); i++)
	{
		fprintf(fp, "%f %f %f ", m_vecFieldBox[i].vPosition.x, m_vecFieldBox[i].vPosition.y, m_vecFieldBox[i].vPosition.z);
		fprintf(fp, "%f %f %f ", m_vecFieldBox[i].vScaling.x, m_vecFieldBox[i].vScaling.y, m_vecFieldBox[i].vScaling.z);
		fprintf(fp, "%f\n", m_vecFieldBox[i].fAngleY);
	}
	fclose(fp);

	if (m_vecFieldNodeSphere.size() == NULL) return;
	// 노드 세이브
	fopen_s(&fp, "SaveFieldPath/FieldPath.txt", "w");
	for (unsigned int i = 0; i < m_vecFieldNodeSphere.size(); i++)
	{
		fprintf(fp, "%f %f %f ", m_vecFieldNodeSphere[i].vCenter.x, m_vecFieldNodeSphere[i].vCenter.y, m_vecFieldNodeSphere[i].vCenter.z);
		fprintf(fp, "%d", m_vecFieldNodeSphere[i].vecLink.size());
		fprintf(fp, "\n");
		for (unsigned int j = 0; j < m_vecFieldNodeSphere[i].vecLink.size(); j++)
		{
			fprintf(fp, "%d %f\n", m_vecFieldNodeSphere[i].vecLink[j].nIndex, m_vecFieldNodeSphere[i].vecLink[j].fCost);
		}
	}
	fclose(fp);

	if (m_vecNodeLine.size() == NULL) return;
	// 노드 라인 세이브
	fopen_s(&fp, "SaveFieldPath/PathLine.txt", "w");
	for (unsigned int i = 0; i < m_vecNodeLine.size(); i++)
	{
		fprintf(fp, "%f %f %f\n", m_vecNodeLine[i].p.x, m_vecNodeLine[i].p.y, m_vecNodeLine[i].p.z);
	}
	fclose(fp);
}

void cSaveLoad::LoadFieldObj()
{
	m_vecFieldObj.clear();
	m_vecFieldBox.clear();
	m_vecFieldNodeSphere.clear();
	m_vecNodeLine.clear();

	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vScal;
	float		fAngleY;
	int			nKind;
	int			nSize;
	vector<NODE> vecNode;

	FILE* fp = NULL;

	// 오브젝트 로드
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
	
	// 충돌 박스 로드
	fopen_s(&fp, "SaveFieldCollisionBox/FieldBox.txt", "r");
	while (true)
	{
		if (feof(fp)) break;
	
		fscanf_s(fp, "%f %f %f %f %f %f %f",
			&vPos.x, &vPos.y, &vPos.z,
			&vScal.x, &vScal.y, &vScal.z,
			&fAngleY);
	
		CreateBox(NULL, vScal, vPos, fAngleY);
	}
	fclose(fp);

	// 노드 로드
	fopen_s(&fp, "SaveFieldPath/FieldPath.txt", "r");
	while (true)
	{
		if (feof(fp)) break;

		fscanf_s(fp, "%f %f %f %d\n", &vPos.x, &vPos.y, &vPos.z, &nSize);

		vecNode.resize(nSize);

		for (int i = 0; i < vecNode.size(); i++)
		{
			fscanf_s(fp, "%d %f\n", &vecNode[i].nIndex, &vecNode[i].fCost);
		}

		CreateNodeSphere(NULL, vPos, vecNode);
	}
	fclose(fp);

	// 노드의 크기만큼 다익스트라 갱신값 사이즈 초기화
	CostSetup(m_vecFieldNodeSphere.size());

	// 노드 라인 로드
	fopen_s(&fp, "SaveFieldPath/PathLine.txt", "r");
	while (true)
	{
		if (feof(fp)) break;

		fscanf_s(fp, "%f %f %f\n", &vPos.x, &vPos.y, &vPos.z);

		ST_PC_VERTEXT v;
		v.p = vPos;
		v.c = D3DCOLOR_XRGB(255, 255, 255);

		m_vecNodeLine.push_back(v);
	}
	fclose(fp);
}

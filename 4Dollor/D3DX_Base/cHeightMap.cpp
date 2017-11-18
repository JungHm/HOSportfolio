#include "stdafx.h"
#include "cHeightMap.h"

cHeightMap::cHeightMap()
	: m_pMesh(NULL)
	, m_pTexture(NULL)
	, m_nRow(0)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cHeightMap::~cHeightMap()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pTexture);
}

void cHeightMap::Setup(char * szFolder, char * szRow, char * szTexture)
{
	string sFolder(szFolder);
	string sRow = sFolder + string(szRow);
	string sTex = sFolder + string(szTexture);

	m_pTexture = g_pTextureManager->GetTexture(sTex);

	FILE* fp = NULL;
	fopen_s(&fp, sRow.c_str(), "rb");

	fseek(fp, 0, SEEK_END);
	int nFileSize = ftell(fp);
	m_nRow = (int)(sqrt((float)nFileSize + 0.0001f));
	int nNumTile = m_nRow - 1;
	fseek(fp, 0, SEEK_SET);

	m_vecVertex.resize(nFileSize);

	for (int i = 0; i < nFileSize; i++)
	{
		ST_PNT_VERTEXT v;
		v.p = D3DXVECTOR3(i % m_nRow, (unsigned char)fgetc(fp) * 0.2f, i / m_nRow);
		v.n = D3DXVECTOR3(0, 1, 0);
		v.t = D3DXVECTOR2((i % m_nRow) / (float)(m_nRow - 1), (i / m_nRow) / (float)(m_nRow - 1));

		m_vecVertex[i] = v;
	}

	fclose(fp);

	// 버텍스 생성
	for (int x = 1; x < nNumTile; x++)
	{
		for (int z = 1; z < nNumTile; z++)
		{
			int nLeft	= (z + 0) * m_nRow + (x - 1);
			int nRight	= (z + 0) * m_nRow + (x + 1);
			int nUp		= (z + 1) * m_nRow + (x + 0);
			int nDown	= (z - 1) * m_nRow + (x + 0);

			D3DXVECTOR3 vLeftToRight = m_vecVertex[nRight].p - m_vecVertex[nLeft].p;
			D3DXVECTOR3 vDownToUp = m_vecVertex[nUp].p - m_vecVertex[nDown].p;
			D3DXVECTOR3 vNormal;

			D3DXVec3Cross(&vNormal, &vDownToUp, &vLeftToRight);
			D3DXVec3Normalize(&vNormal, &vNormal);

			m_vecVertex[z * m_nRow + x].n = vNormal;
		}
	}

	// 인덱스 생성
	vector<DWORD>	vecIndex;
	vecIndex.resize(nNumTile * nNumTile * 2 * 3);

	for (int x = 0; x < nNumTile; x++)
	{
		for (int z = 0; z < nNumTile; z++)
		{
			int n0 = (z + 0) * m_nRow + (x + 0);
			int n1 = (z + 1) * m_nRow + (x + 0);
			int n2 = (z + 0) * m_nRow + (x + 1);
			int n3 = (z + 1) * m_nRow + (x + 1);

			vecIndex.push_back(n0);
			vecIndex.push_back(n1);
			vecIndex.push_back(n2);

			vecIndex.push_back(n3);
			vecIndex.push_back(n2);
			vecIndex.push_back(n1);
		}
	}

	// 빈 매쉬 생성
	D3DXCreateMeshFVF(vecIndex.size() / 3, m_vecVertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT, ST_PNT_VERTEXT::FVF, g_pD3DDevice, &m_pMesh);

	// 버텍스 버퍼 생성
	ST_PNT_VERTEXT* pV = NULL;
	m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &m_vecVertex[0], m_vecVertex.size() * sizeof(ST_PNT_VERTEXT));
	m_pMesh->UnlockVertexBuffer();

	// 인덱스 버퍼 생성
	DWORD* pI = NULL;
	m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(DWORD));
	m_pMesh->UnlockIndexBuffer();

	// 어트리 뷰트 버퍼 생성
	DWORD* pA = NULL;
	m_pMesh->LockAttributeBuffer(0, &pA);
	ZeroMemory(pA, vecIndex.size() / 3 * sizeof(DWORD));
	m_pMesh->UnlockAttributeBuffer();

	// 최적화
	vector<DWORD> vecAdj(vecIndex.size());
	m_pMesh->GenerateAdjacency(0.0f, &vecAdj[0]);
	m_pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, &vecAdj[0], 0, 0, 0);

	// 메터리얼
	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
	m_mtl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_mtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_mtl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

void cHeightMap::Render()
{
	D3DXMATRIXA16 matS, matR, matT;
	
	D3DXMatrixScaling(&matS, 17.0f, 8.0f, 15.0f);
	D3DXMatrixRotationY(&matR, D3DX_PI);
	D3DXMatrixTranslation(&matT, 330.0f, -50.0f, 340.0f);

	m_matWorld = matS * matR * matT;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetMaterial(&m_mtl);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	m_pMesh->DrawSubset(0);
}

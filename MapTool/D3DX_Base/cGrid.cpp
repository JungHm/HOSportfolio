#include "stdafx.h"
#include "cGrid.h"

cGrid::cGrid()
	: m_pMesh(NULL)
	, m_pTexTure(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cGrid::~cGrid()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pTexTure);
}

void cGrid::Setup(IN char* szFolder, IN char* szFile, IN int nRow, IN int nCol, IN float fSize)
{
	string sFullPath(szFolder);
	sFullPath += (string("/") + string(szFile));
	m_pTexTure = g_pTextureManager->GetTexture(sFullPath);

	m_nRow = nRow;			// �� 
	m_nCol = nCol;			// ��
	m_fTileSize = fSize;	// Ÿ�� �ϳ��� ũ��

	m_nTotalVertex = (m_nRow + 1) * (m_nCol + 1);		// �� ���ؽ� ���� = (�� ���� + 1) x (�� ���� + 1)
	m_nTotalIndex = m_nRow * m_nCol * 6;				// �� �ε��� ���� = �� x �� x 6
	m_fStartPosX = -1.0f * m_nCol * m_fTileSize * 0.5f; // x ��ǥ ���� ��ġ = -1.0f x �� x ũ��(����) x 0.5f(1/2)
	m_fStartPosZ = m_nRow * m_fTileSize * 0.5f;			// z ��ǥ ���� ��ġ = �� x ũ��(����) x 0.5f(1/2)

	// ����� �Ž�
	//D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pSphereMesh, NULL);

	m_vecVertex.resize(m_nTotalVertex);		// �� ���ؽ� ���� ��ŭ ��������
	int nVIndex = 0;						// ���ؽ� ���� Ž�� �ε���

	// ���ؽ� ����
	for (int z = 0; z <= m_nRow; z++)		// ��(z��)
	{
		for (int x = 0; x <= m_nCol; x++)	// ��(x��)
		{
			ST_PNT_VERTEXT v;
			// ���� ��ǥ
			v.p.x = m_fStartPosX + (x * m_fTileSize);
			v.p.y = 0.0f;
			v.p.z = m_fStartPosZ + (-1.0f) * (z * m_fTileSize);
			// �ؽ��� ��ǥ
			v.t.x = ONE_XPER * x;
			v.t.y = ONE_YPER * z;
			// ���ؽ� ���Ϳ� ����
			m_vecVertex[nVIndex] = v;
			// ���ؽ� ���� �ε��� ����
			nVIndex++;
			//// ����� ����
			//m_eSphere[z][x].fRadius = 0.5f;
			//m_eSphere[z][x].vCenter = D3DXVECTOR3(v.p.x, 0, v.p.z);
			//m_eSphere[z][x].isWall = false;
		}
	}

	m_vecIndex.resize(m_nTotalIndex);		// �� �ε��� ���� ��ŭ ��������
	int nIIndex = 0;						// �ε��� ���� Ž�� �ε���

	// �ε��� ����
	for (int z = 0; z < m_nRow; z++)		// ��(z��)
	{
		for (int x = 0; x < m_nCol; x++)	// ��(x��)
		{
			m_vecIndex[nIIndex++] = DWORD(z * (m_nCol + 1) + x);
			m_vecIndex[nIIndex++] = DWORD((z + 1) * (m_nCol + 1) + x + 1);
			m_vecIndex[nIIndex++] = DWORD((z + 1) * (m_nCol + 1) + x);

			m_vecIndex[nIIndex++] = DWORD(z * (m_nCol + 1) + x);
			m_vecIndex[nIIndex++] = DWORD(z * (m_nCol + 1) + x + 1);
			m_vecIndex[nIIndex++] = DWORD((z + 1) * (m_nCol + 1) + x + 1);
		}
	}

	D3DXVECTOR3 v1, v2, n;
	for (int i = 0; i < m_nTotalIndex; i += 3)
	{
		// ���� ���� ����
		v1 = m_vecVertex[m_vecIndex[i + 1]].p - m_vecVertex[m_vecIndex[i]].p;
		v2 = m_vecVertex[m_vecIndex[i + 2]].p - m_vecVertex[m_vecIndex[i]].p;

		D3DXVec3Cross(&n, &v1, &v2);
		D3DXVec3Normalize(&n, &n);

		m_vecVertex[m_vecIndex[i]].n = n;
		m_vecVertex[m_vecIndex[i + 1]].n = n;
		m_vecVertex[m_vecIndex[i + 2]].n = n;
	}

	// ���͸��� ����
	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
	m_mtl.Ambient  = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_mtl.Diffuse  = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_mtl.Specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	// �� �Ž� ����
	D3DXCreateMeshFVF(m_nTotalIndex / 3, m_nTotalVertex, D3DXMESH_MANAGED | D3DXMESH_32BIT, ST_PNT_VERTEXT::FVF, g_pD3DDevice, &m_pMesh);

	// ���ؽ� ���� 
	ST_PNT_VERTEXT* pV = NULL;
	m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &m_vecVertex[0], m_nTotalVertex * sizeof(ST_PNT_VERTEXT));
	m_pMesh->UnlockVertexBuffer();

	// �ε��� ����
	DWORD* pI = NULL;
	m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	memcpy(pI, &m_vecIndex[0], m_nTotalIndex * sizeof(DWORD));
	m_pMesh->UnlockIndexBuffer();

	// ��Ʈ����Ʈ ����
	DWORD* pA = NULL;
	m_pMesh->LockAttributeBuffer(0, &pA);
	ZeroMemory(pA, m_nTotalIndex / 3 * sizeof(DWORD));
	m_pMesh->UnlockAttributeBuffer();

	// ����ȭ
	vector<DWORD> vecAdj(m_nTotalIndex);
	m_pMesh->GenerateAdjacency(0.0f, &vecAdj[0]);
	m_pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, &vecAdj[0], 0, 0, 0);

	// �߽� �� ����
	ST_PC_VERTEXT v;
	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(m_fStartPosX, 0.0f, 0.0f);	m_vecAxis.push_back(v);
	v.p = D3DXVECTOR3(-m_fStartPosX, 0.0f, 0.0f);	m_vecAxis.push_back(v);
	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(0.0f, m_fStartPosX, 0.0f);	m_vecAxis.push_back(v);
	v.p = D3DXVECTOR3(0.0f, -m_fStartPosX, 0.0f);	m_vecAxis.push_back(v);
	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(0.0f, 0.0f, m_fStartPosZ);	m_vecAxis.push_back(v);
	v.p = D3DXVECTOR3(0.0f, 0.0f, -m_fStartPosZ);	m_vecAxis.push_back(v);

	// ��ŷ�� ���ؽ� ����
	ST_PC_VERTEXT vp;
	vp.c = D3DCOLOR_XRGB(255, 255, 255);
	vp.p = D3DXVECTOR3(m_fStartPosX, 0.0f, m_fStartPosZ);
	m_vecPicVertex.push_back(vp);
	vp.p = D3DXVECTOR3(-m_fStartPosX, 0.0f, -m_fStartPosZ);
	m_vecPicVertex.push_back(vp);
	vp.p = D3DXVECTOR3(m_fStartPosX, 0.0f, -m_fStartPosZ);
	m_vecPicVertex.push_back(vp);

	vp.p = D3DXVECTOR3(m_fStartPosX, 0.0f, m_fStartPosZ);
	m_vecPicVertex.push_back(vp);
	vp.p = D3DXVECTOR3(-m_fStartPosX, 0.0f, m_fStartPosZ);
	m_vecPicVertex.push_back(vp);
	vp.p = D3DXVECTOR3(-m_fStartPosX, 0.0f, -m_fStartPosZ);
	m_vecPicVertex.push_back(vp);
}

void cGrid::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	//D3DXMATRIXA16	matWorld;

	//// ����� ����
	//for (int i = 0; i <= MAX_ROW; i++)
	//{
	//	for (int j = 0; j <= MAX_COL; j++)
	//	{
	//		D3DXMatrixIdentity(&matWorld);
	//		matWorld._41 = m_eSphere[i][j].vCenter.x;
	//		matWorld._42 = m_eSphere[i][j].vCenter.y;
	//		matWorld._43 = m_eSphere[i][j].vCenter.z;
	//
	//		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//		g_pD3DDevice->SetTexture(0, NULL);
	//
	//		m_pSphereMesh->DrawSubset(0);
	//	}
	//}

	// �׸��� ����
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetMaterial(&m_mtl);
	g_pD3DDevice->SetTexture(0, m_pTexTure);
	m_pMesh->DrawSubset(0);

	// ��, ��ŷ�� ���ؽ� ����
	if (KEY->m_isWireFrame)
	{
		g_pD3DDevice->SetTexture(0, NULL);
		g_pD3DDevice->SetFVF(ST_PC_VERTEXT::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecAxis.size() / 2, &m_vecAxis[0], sizeof(ST_PC_VERTEXT));
		g_pD3DDevice->SetFVF(ST_PC_VERTEXT::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecPicVertex.size() / 3, &m_vecPicVertex[0], sizeof(ST_PC_VERTEXT));
	}
}
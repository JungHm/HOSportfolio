#include "stdafx.h"
#include "cXLoader.h"
#include "cAllocateHierarchy.h"
#include "cMtlTex.h"

cXLoader::cXLoader()
	: m_pFrameRoot(nullptr)
{
	m_sPath = L"Tassadar/Tassadar.X";
}

cXLoader::~cXLoader()
{
	cAllocateHierarchy m_pAlloc;
	D3DXFrameDestroy(m_pFrameRoot, &m_pAlloc);
	SAFE_RELEASE(m_pAnimControl);
}

void cXLoader::Destroy()
{

}

void cXLoader::XfileLoad(IN wstring m_sPath)
{
	cAllocateHierarchy m_pAlloc;

	HRESULT hr = D3DXLoadMeshHierarchyFromX(m_sPath.c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&m_pAlloc,
		NULL,
		&m_pFrameRoot,
		&m_pAnimControl);
	D3DXMATRIX matW;
	D3DXMatrixIdentity(&matW);

	D3DXMatrixTranslation(&matW, 0, 0, 0);

	//SetupWorldMatrix(m_pFrameRoot, &matW);
	SetupBoneMatrixPtrs((ST_BONE*)m_pFrameRoot);

	for (UINT i = 0; i < m_pAnimControl->GetMaxNumTracks(); i++)
	{
		m_pAnimControl->SetTrackEnable(i, TRUE);
	} //animation Track ��Ȱ��ȭ.
	m_pAnimControl->SetTrackEnable(0, TRUE);

}



void cXLoader::Update()
{

	UpdateSkinnedMesh(m_pFrameRoot);
}


void cXLoader::Render(D3DXMATRIXA16& matRT)
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_pD3DDevice->LightEnable(0, true);
	ST_BONE* pBone = (ST_BONE*)m_pFrameRoot;
	RecursiveFrameRender(pBone, &pBone->matWorldTM, matRT);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

}

void cXLoader::SetupBoneMatrixPtrs(D3DXFRAME * pFrame)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;

	// �� �������� �޽� �����̳ʿ� �ִ� pSkinInfo�� �̿��Ͽ� ����޴� ��� 
	// �������� ��Ʈ������ ppBoneMatrixPtrs�� �����Ѵ�.

	// pSkinInfo->GetNumBones() ���� ����޴� ���� ������ ã��.
	// pSkinInfo->GetBoneName(i) �� i�� �������� �̸��� ã��
	// D3DXFrameFind(��Ʈ ������, ������ �̸�) �� �������� ã��.
	// ã�Ƽ� �����Ʈ������ �ɾ����.

	//��������� ��� �����ӿ� ���ؼ� ����.
	if (pBoneMesh)
	{
		if (pBoneMesh->pSkinInfo)
		{
			DWORD nNumBones = pBoneMesh->pSkinInfo->GetNumBones();

			string sBoneName;
			for (size_t i = 0; i < nNumBones; ++i)
			{
				sBoneName = pBoneMesh->pSkinInfo->GetBoneName(i);
				ST_BONE* pFindedBone = (ST_BONE*)D3DXFrameFind(m_pFrameRoot, sBoneName.c_str());
				pBoneMesh->ppBoneMatrixPtrs[i] = &pFindedBone->matWorldTM;
				//pTargetBone->matWorldTM = pTargetBone->TransformationMatrix * ((ST_BONE*)m_pFrameRoot)->matWorldTM;
			}
		}
	}
	if (pBone->pFrameSibling)
	{
		SetupBoneMatrixPtrs(pBone->pFrameSibling);
	}
	if (pBone->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs(pBone->pFrameFirstChild);
	}
}

void cXLoader::UpdateSkinnedMesh(D3DXFRAME * pFrame)
{// pCurrentBoneMatrices �� ����Ͻÿ�
 // pCurrentBoneMatrices = pBoneOffsetMatrices * ppBoneMatrixPtrs 

 // 	BYTE* src = NULL;
 // 	BYTE* dest = NULL;
 // 
 // 	pBoneMesh->pOrigMesh->LockVertexBuffer( D3DLOCK_READONLY, (void**)&src );
 // 	pBoneMesh->MeshData.pMesh->LockVertexBuffer( 0, (void**)&dest );
 // 
 // 	//MeshData.pMesh�� ������Ʈ �����ش�.
 // 	pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
 // 		pBoneMesh->pCurrentBoneMatrices, NULL, src, dest );
 // 
 // 	pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
 // 	pBoneMesh->pOrigMesh->UnlockVertexBuffer();

 //��������� ��� �����ӿ� ���ؼ� ����

	ST_BONE* pBone = (ST_BONE*)pFrame;
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;

	if (pBoneMesh)
	{
		DWORD nNumBones = pBoneMesh->pSkinInfo->GetNumBones();
		for (size_t i = 0; i < nNumBones; ++i)
		{
			pBoneMesh->pCurrentBoneMatrices[i] = pBoneMesh->pBoneOffsetMatrices[i] * (*pBoneMesh->ppBoneMatrixPtrs[i]);
		}
		BYTE* src = NULL;
		BYTE* dest = NULL;

		pBoneMesh->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src);
		pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&dest);

		//MeshData.pMesh�� ������Ʈ �����ش�.
		pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
			pBoneMesh->pCurrentBoneMatrices, NULL, src, dest);

		pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
		pBoneMesh->pOrigMesh->UnlockVertexBuffer();
	}
	if (pBone->pFrameSibling)
	{
		UpdateSkinnedMesh(pBone->pFrameSibling);
	}
	if (pBone->pFrameFirstChild)
	{
		UpdateSkinnedMesh(pBone->pFrameFirstChild);
	}

}

void cXLoader::RecursiveFrameRender(D3DXFRAME * pParent, D3DXMATRIXA16 * pParentWorldTM, D3DXMATRIXA16& matRT)
{
	ST_BONE* pBone = (ST_BONE*)pParent;
	D3DXMATRIXA16 matW;
	D3DXMatrixIdentity(&matW);

	matW = pParent->TransformationMatrix * (*pParentWorldTM);

	D3DXMATRIXA16 matWorld, matS; D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, 0.05f, 0.05f, 0.05f);
	matWorld = matS*matRT;
	pBone->matWorldTM = matW;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	//m_pMesh->DrawSubset(0);//����
	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		//g_pD3DDevice->SetTexture(0, pFrame->pMeshContainer->pMaterials);
		for (size_t i = 0; i < pBoneMesh->numSubset; ++i)
		{
			g_pD3DDevice->SetTexture(0, pBoneMesh->vecMtlTex[i]->GetTexture());
			g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtlTex[i]->GetMaterial());
			pBoneMesh->MeshData.pMesh->DrawSubset(i);
		}
	}
	//�ڽ�
	if (pParent->pFrameFirstChild)
	{
		RecursiveFrameRender(pParent->pFrameFirstChild, &pBone->matWorldTM, matRT);
	}
	//����
	if (pParent->pFrameSibling)
	{
		RecursiveFrameRender(pParent->pFrameSibling, pParentWorldTM, matRT);
	}
}



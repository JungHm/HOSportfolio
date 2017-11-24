#include "stdafx.h"
#include "cAllocateHierarchy.h"
#include "cMtlTex.h"

cAllocateHierarchy::cAllocateHierarchy()
{
}


cAllocateHierarchy::~cAllocateHierarchy()
{
}

STDMETHODIMP cAllocateHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME * ppNewFrame)
{
	ST_BONE* pBone = new ST_BONE;
	ZeroMemory(pBone, sizeof(ST_BONE));


	//새로만든 Bond Node에 이름 복사.
	if (Name)
	{
		pBone->Name = new char[strlen(Name) + 1];

		strcpy(pBone->Name, Name);
		//strcpy_s(pFrame->Name, strlen(Name) + 1, Name);


	}
	D3DXMatrixIdentity(&pBone->TransformationMatrix);
	D3DXMatrixIdentity(&pBone->matWorldTM);

	(*ppNewFrame) = pBone;
	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::CreateMeshContainer(LPCSTR Name, CONST D3DXMESHDATA * pMeshData, CONST D3DXMATERIAL * pMaterials, CONST D3DXEFFECTINSTANCE * pEffectInstance, DWORD NumMaterials, CONST DWORD * pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER * ppNewMeshContainer)
{
	ST_BONE_MESH* pBoneMesh = new ST_BONE_MESH;
	ZeroMemory(pBoneMesh, sizeof(ST_BONE_MESH));

	//THIS_ LPCSTR Name,
	pBoneMesh->Name = new char[strlen(Name) + 1];
	
	//CONST D3DXMATERIAL *pMaterials,	//배열
	//DWORD NumMaterials,
	if (pMaterials)
	{
		pBoneMesh->pMaterials = new D3DXMATERIAL[NumMaterials];
		pBoneMesh->NumMaterials = NumMaterials;
		for (size_t i = 0; i < NumMaterials; ++i)
		{
			string sPath;
			if (pMaterials[i].pTextureFilename)
				sPath = "Texture/" + string(pMaterials[i].pTextureFilename);

			cMtlTex* pMtlTex = new cMtlTex;
			if (pMaterials[i].pTextureFilename)
				pMtlTex->SetTexture(g_pTextureManager->GetTexture(sPath));
			else
				pMtlTex->SetTexture(NULL);

			pMtlTex->GetMaterial() = pMaterials[i].MatD3D;
			pBoneMesh->vecMtlTex.push_back(pMtlTex);


			//필요해질때까지 주석
			//pBoneMesh->pMaterials[i].MatD3D = pMaterials[i].MatD3D;
			//pBoneMesh->pMaterials[i].pTextureFilename = new char[strlen(pMaterials[i].pTextureFilename) + 1];
			//strcpy(pBoneMesh->pMaterials[i].pTextureFilename, pMaterials[i].pTextureFilename);

			//CONST D3DXMESHDATA *pMeshData,
			if (pMeshData && D3DXMESHTYPE_MESH == pMeshData->Type)
			{
				pBoneMesh->MeshData.Type = pMeshData->Type;

				pMeshData->pMesh->CloneMeshFVF(D3DXMESH_MANAGED,
					pMeshData->pMesh->GetFVF(),
					g_pD3DDevice,
					&pBoneMesh->MeshData.pMesh);

				//원본 메쉬도 복사
				pBoneMesh->MeshData.pMesh->CloneMeshFVF(D3DXMESH_MANAGED,
					pBoneMesh->MeshData.pMesh->GetFVF(),
					g_pD3DDevice,
					&pBoneMesh->pOrigMesh);
				pMeshData->pMesh->GetAttributeTable(0, &pBoneMesh->numSubset);
			}
		}
	}
	//LPD3DXSKININFO pSkinInfo
	if (pSkinInfo)
	{
		pSkinInfo->Clone(&pBoneMesh->pSkinInfo);
	}

	// OBB
	if (pMeshData && pMeshData->pMesh)
	{
		D3DXVECTOR3	vMin(0, 0, 0), vMax(0, 0, 0);

		LPVOID pV = NULL;
		pMeshData->pMesh->LockVertexBuffer(0, &pV);

		D3DXComputeBoundingBox((D3DXVECTOR3*)pV,
			pMeshData->pMesh->GetNumVertices(),
			D3DXGetFVFVertexSize(pMeshData->pMesh->GetFVF()),
			&vMin, &vMax);

		D3DXVec3Minimize(&m_vMin, &m_vMin, &vMin);
		D3DXVec3Maximize(&m_vMax, &m_vMax, &vMax);

		pMeshData->pMesh->UnlockVertexBuffer();
	}

	DWORD nNumBones = pSkinInfo->GetNumBones();

	pBoneMesh->pBoneOffsetMatrices = new D3DXMATRIXA16[nNumBones];
	pBoneMesh->pCurrentBoneMatrices = new D3DXMATRIXA16[nNumBones];
	pBoneMesh->ppBoneMatrixPtrs = new LPD3DXMATRIX[nNumBones];
	// step 4. 동적 할당된 pBoneOffsetMatrices 매트릭스에 값 저장.
	for (UINT i = 0; i < nNumBones; ++i)
	{
		pBoneMesh->pBoneOffsetMatrices[i] = *(pSkinInfo->GetBoneOffsetMatrix(i));
	}

	*ppNewMeshContainer = pBoneMesh;
	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	ST_BONE* pBone = (ST_BONE*)pFrameToFree;
	SAFE_DELETE_ARRAY(pBone->Name);

	SAFE_DELETE(pBone);
	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pMeshContainerToFree;

	SAFE_RELEASE(pBoneMesh->MeshData.pMesh);
	SAFE_RELEASE(pBoneMesh->pSkinInfo);
	SAFE_RELEASE(pBoneMesh->pOrigMesh);
	for (int i = 0; i < pBoneMesh->vecMtlTex.size(); i++)
	{
		pBoneMesh->vecMtlTex[i]->GetTexture()->Release();
	}


	SAFE_DELETE_ARRAY(pBoneMesh->pCurrentBoneMatrices);
	SAFE_DELETE_ARRAY(pBoneMesh->pBoneOffsetMatrices);
	SAFE_DELETE_ARRAY(pBoneMesh->ppBoneMatrixPtrs);
	pBoneMesh->vecMtlTex.clear();
	SAFE_DELETE(pBoneMesh);

	return S_OK;
}

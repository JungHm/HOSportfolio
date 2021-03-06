#include "stdafx.h"
#include "cXLoader.h"
#include "cAllocateHierarchy.h"
#include "cMtlTex.h"

cXLoader::cXLoader()
	: m_pFrameRoot(NULL)
{
	m_sPath = L"Tassadar/Tassadar.X";
	ShaderSet = false;
}

cXLoader::~cXLoader()
{
	cAllocateHierarchy m_pAlloc;
	D3DXFrameDestroy(m_pFrameRoot, &m_pAlloc);
	SAFE_RELEASE(m_pAnimControl);
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
	m_vMax = m_pAlloc.GetMax();
	m_vMin = m_pAlloc.GetMin();

	D3DXMatrixTranslation(&matW, 0, 0, 0);

	//SetupWorldMatrix(m_pFrameRoot, &matW);
	SetupBoneMatrixPtrs((ST_BONE*)m_pFrameRoot);

	for (UINT i = 0; i < m_pAnimControl->GetMaxNumTracks(); i++)
	{
		m_pAnimControl->SetTrackEnable(i, TRUE);
	} //animation Track 搾醗失鉢.
	m_pAnimControl->SetTrackEnable(0, TRUE);

	//FX settings
	/*ST_BONE* pBone = (ST_BONE*)m_pFrameRoot;
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
	g_FXLoad->InitFx(pBoneMesh->MeshData.pMesh->GetFVF());*/

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

	// 唖 覗傾績税 五獣 珍砺戚格拭 赤澗 pSkinInfo研 戚遂馬食 慎狽閤澗 乞窮 
	// 覗傾績税 古闘遣什研 ppBoneMatrixPtrs拭 尻衣廃陥.

	// pSkinInfo->GetNumBones() 生稽 慎狽閤澗 沙税 鯵呪研 達製.
	// pSkinInfo->GetBoneName(i) 稽 i腰 覗傾績税 戚硯聖 達製
	// D3DXFrameFind(欠闘 覗傾績, 覗傾績 戚硯) 稽 覗傾績聖 達製.
	// 達焼辞 杉球古闘遣什研 杏嬢操虞.

	//仙瑛旋生稽 乞窮 覗傾績拭 企背辞 叔楳.
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
{// pCurrentBoneMatrices 研 域至馬獣神
 // pCurrentBoneMatrices = pBoneOffsetMatrices * ppBoneMatrixPtrs 

 // 	BYTE* src = NULL;
 // 	BYTE* dest = NULL;
 // 
 // 	pBoneMesh->pOrigMesh->LockVertexBuffer( D3DLOCK_READONLY, (void**)&src );
 // 	pBoneMesh->MeshData.pMesh->LockVertexBuffer( 0, (void**)&dest );
 // 
 // 	//MeshData.pMesh聖 穣汽戚闘 獣佃層陥.
 // 	pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
 // 		pBoneMesh->pCurrentBoneMatrices, NULL, src, dest );
 // 
 // 	pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
 // 	pBoneMesh->pOrigMesh->UnlockVertexBuffer();

 //仙瑛旋生稽 乞窮 覗傾績拭 企背辞 叔楳

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

		//MeshData.pMesh聖 穣汽戚闘 獣佃層陥.
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

	//m_pMesh->DrawSubset(0);//兄希
	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		//g_pD3DDevice->SetTexture(0, pFrame->pMeshContainer->pMaterials);
		for (size_t i = 0; i < pBoneMesh->numSubset; ++i)
		{

			g_pD3DDevice->SetTexture(0, pBoneMesh->vecMtlTex[i]->GetTexture());
			g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtlTex[i]->GetMaterial());
			pBoneMesh->MeshData.pMesh->DrawSubset(i);


			//拾戚希 旋遂 乞切戚滴せせせせせせせ

			//if (!ShaderSet)
			//{
			//	g_FXLoad->InitFx(pBoneMesh->MeshData.pMesh->GetFVF());
			//	ShaderSet = true;
			//}
			//g_pD3DDevice->SetTexture(0, pBoneMesh->vecMtlTex[i]->GetTexture());
			//g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtlTex[i]->GetMaterial());
			//g_FXLoad->SetupFx(pBoneMesh->vecMtlTex[i]->GetTexture(), pBoneMesh->pCurrentBoneMatrices);

			////g_pD3DDevice->SetVertexDeclaration(g_sDecl);
			//

			//D3DXHANDLE hTech = g_sEffect->GetTechniqueByName("Mosaik");
			//g_sEffect->SetTechnique(hTech);
			//g_sEffect->Begin(NULL, NULL);
			//g_sEffect->BeginPass(0);
			//
			//pBoneMesh->MeshData.pMesh->DrawSubset(i);

			//g_sEffect->EndPass();
			//g_sEffect->End();
		}
	}
	//切縦
	if (pParent->pFrameFirstChild)
	{
		RecursiveFrameRender(pParent->pFrameFirstChild, &pBone->matWorldTM, matRT);
	}
	//莫薦
	if (pParent->pFrameSibling)
	{
		RecursiveFrameRender(pParent->pFrameSibling, pParentWorldTM, matRT);
	}
}



#include "stdafx.h"
#include "cXLoader.h"
#include "cAllocateHierarchy.h"
#include "cMtlTex.h"

cXLoader::cXLoader()
	: m_pAlloc(nullptr)
	, m_pFrameRoot(nullptr)
	, m_pMesh(nullptr)
	, m_ft(0.1f)
	, vPos(0, 0, 0)
	, vDir(0, 0, 1)
{
	m_dTimeCurrent = 0;
	m_sPath = L"Tassadar/Tassadar.X";
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matR);
	dwCurr = 0;

	m_State = STAND;
}

HRESULT cXLoader::InitGeometry()
{
	LPD3DXBUFFER pMtlBuffer; //파일에서 불러온 재질정보 *임시로* 저장할 버퍼.

	if (FAILED(D3DXLoadMeshFromX(L"tiger.x",
		D3DXMESH_SYSTEMMEM/*시스템 메모리에 버퍼 보관*/,
		g_pD3DDevice,
		NULL,/*ppAdjacency???*/
		&pMtlBuffer,//파일에서 불러온 재질 임시로 저장할 버퍼.
		NULL,
		&m_NumMtl,//재질 개수
		&m_pMesh//Mesh 정보 담을 객체.
	)))
	{
		return E_FAIL;
	}

	//재질 정보와 텍스쳐 정보 따로 뽑아냄.

	D3DXMATERIAL* d3dxmtl = (D3DXMATERIAL*)pMtlBuffer->GetBufferPointer();

	//Material 개수만큼 Material구조체 배열 생성.
	m_pMtl = new D3DMATERIAL9[m_NumMtl];

	//Material 개수만큼 Texture 배열 생성.

	m_pTexture = new LPDIRECT3DTEXTURE9[m_NumMtl];

	for (DWORD i = 0; i < m_NumMtl; i++)
	{
		m_pMtl[i] = d3dxmtl[i].MatD3D; //Material정보 복사.
		m_pMtl[i].Ambient = m_pMtl[i].Diffuse;
		m_pTexture[i] = NULL; //texture 객체 NULL 초기화.

		if (d3dxmtl[i].pTextureFilename != NULL && strlen(d3dxmtl[i].pTextureFilename) > 0)
		{
			if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, (LPCWSTR)d3dxmtl[i].pTextureFilename, &m_pTexture[i])))
			{
				return E_FAIL;
			}
		}
	}

	pMtlBuffer->Release(); //임시 저장 버퍼 해제.

						   //IDirect3DVertexBuffer9* Temp;
						   //m_pMesh->GetVertexBuffer(&Temp);
						   //ST_PNT_VERTEXT* vTemp;
						   //Temp->Lock(0, 0, (void**)&vTemp, 0);
						   //D3DXVECTOR3 x = vTemp[0].n;
						   //	Temp->Unlock();
	return S_OK;
}

void cXLoader::SetUp()
{
	m_pAlloc = new cAllocateHierarchy;

	HRESULT hr = D3DXLoadMeshHierarchyFromX(m_sPath.c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		m_pAlloc,
		NULL,
		&m_pFrameRoot,
		&m_pAnimControl);
	//assert(hr == S_OK);
	D3DXMATRIX matW;
	D3DXMatrixIdentity(&matW);

	D3DXMatrixTranslation(&matW, 1, 0, 0);

	//SetupWorldMatrix(m_pFrameRoot, &matW);
	SetupBoneMatrixPtrs((ST_BONE*)m_pFrameRoot);

	for (int i = 0; i < m_pAnimControl->GetMaxNumTracks(); i++)
	{
		m_pAnimControl->SetTrackEnable(i, TRUE);
	} //animation Track 비활성화.
	m_pAnimControl->SetTrackEnable(0, TRUE);
	LPD3DXANIMATIONSET pAS;

	for (DWORD i = 0; i < m_pAnimControl->GetNumAnimationSets(); ++i)
	{
		m_pAnimControl->GetAnimationSet(i, &pAS);

		if (!strncmp(pAS->GetName(), "Attack ", strlen(pAS->GetName())))
		{
			dwAttack = i;
		}
		else if (!strncmp(pAS->GetName(), "Spell ", strlen(pAS->GetName())))
		{
			dwSpell = i;
		}
		else if (!strncmp(pAS->GetName(), "Stand ", strlen(pAS->GetName())))
		{
			dwStand = i;
		}
		else if (!strncmp(pAS->GetName(), "Walk ", strlen(pAS->GetName())))
		{
			dwWalk = i;
		}
	}

	m_pAnimControl->GetAnimationSet(dwAttack, &pAS);
	m_pAnimControl->SetTrackAnimationSet(0, pAS);
	m_pAnimControl->ResetTime();
}

void cXLoader::Update()
{
	m_pAnimControl->AdvanceTime(m_dTimeCurrent, NULL);



	//m_ft += 0.01f;
	//if (m_State != ATTACK)
	m_pAnimControl->AdvanceTime(0.018f, NULL);
	double a = m_pAnimControl->GetTime();
	LPD3DXANIMATIONSET pAS;
	if (GetAsyncKeyState('1') & 0x8000)
	{
		m_State = dwAttack;
	}
	if (GetAsyncKeyState('2') & 0x8000)
	{
		m_State = dwSpell;
	}
	if (GetAsyncKeyState('3') & 0x8000)
	{
		m_State = dwStand;
	}
	if (GetAsyncKeyState('4') & 0x8000)
	{
		m_State = dwWalk;
	}


	LPD3DXANIMATIONSET pASCompare;
	D3DXTRACK_DESC desc;
	switch (m_State)
	{
	case ATTACK:
		m_pAnimControl->GetAnimationSet(dwAttack, &pAS);
		m_pAnimControl->GetTrackAnimationSet(0, &pASCompare);
		if (!strcmp(pAS->GetName(), pASCompare->GetName())) //이미 Idle인 경우.
		{
			m_pAnimControl->GetTrackDesc(0, &desc);
			if (desc.Position  > pAS->GetPeriod())
			{
				m_State = STAND;
			}
			//break;
		}
		else
		{
			m_pAnimControl->SetTrackAnimationSet(0, pAS);
			m_pAnimControl->SetTrackPosition(0, 0);
		}
		break;

	case SPELL:
		m_pAnimControl->GetAnimationSet(dwSpell, &pAS);
		m_pAnimControl->GetTrackAnimationSet(0, &pASCompare);
		if (!strcmp(pAS->GetName(), pASCompare->GetName())) //이미 Idle인 경우.
		{
			m_pAnimControl->GetTrackDesc(0, &desc);
			if (desc.Position  > pAS->GetPeriod())
			{
				m_State = STAND;
				//// 트랙에 있는 키값들을 모두 없앤다.
				//m_pAnimControl->UnkeyAllTrackEvents(dwCurr);
				//m_pAnimControl->UnkeyAllTrackEvents(dwNew);
				//// 현재트랙을 사용하지않는 키값을 현재시간으로부터 블랜딩이 끝나는 시간에 넣는다.
				//m_pAnimControl->KeyTrackEnable(dwCurr, FALSE, m_dTimeCurrent + 0.018f);
				//// 현재트랙의 속도를 현재시간부로 0으로 점차 선형보간한다.
				//m_pAnimControl->KeyTrackSpeed(dwCurr, 0.0f, m_dTimeCurrent, 0.018f, D3DXTRANSITION_LINEAR);
				//// 현재트랙의 가중치를 현재시간부로 0으로 점차 선형보간한다.
				//m_pAnimControl->KeyTrackWeight(dwCurr, 0.0f, m_dTimeCurrent, 0.018f, D3DXTRANSITION_LINEAR);
				//// dwNewTrack을 사용한다.
				//m_pAnimControl->SetTrackEnable(dwNew, TRUE);
				//// 새로운트랙의 속도를 현재시간부로 1로 점차 선형보간한다.
				//m_pAnimControl->KeyTrackSpeed(dwNew, 1.0f, m_dTimeCurrent, 0.018f, D3DXTRANSITION_LINEAR);
				//// 새로운트랙의 가중치를 현재시간부로 1로 점차 선형보간한다.
				//m_pAnimControl->KeyTrackWeight(dwNew, 1.0f, m_dTimeCurrent, 0.018f, D3DXTRANSITION_LINEAR);
			}
			//break;
		}
		else
		{
			m_pAnimControl->SetTrackAnimationSet(0, pAS);
			m_pAnimControl->SetTrackPosition(0, 0);
		}
		break;

	case STAND:
		m_pAnimControl->GetAnimationSet(dwStand, &pAS);
		m_pAnimControl->GetTrackAnimationSet(0, &pASCompare);
		if (!strcmp(pAS->GetName(), pASCompare->GetName())) //이미 Idle인 경우.
		{

			break;
		}
		else
		{
			m_pAnimControl->SetTrackAnimationSet(0, pAS);
			m_pAnimControl->SetTrackPosition(0, 0);
		}
		break;

	case WALK:
		m_pAnimControl->GetAnimationSet(dwWalk, &pAS);
		m_pAnimControl->GetTrackAnimationSet(0, &pASCompare);
		if (!strcmp(pAS->GetName(), pASCompare->GetName())) //이미 Idle인 경우.
		{

			break;
		}
		else
		{
			m_pAnimControl->SetTrackAnimationSet(0, pAS);
			m_pAnimControl->SetTrackPosition(0, 0);
		}
		break;
		//case SELECT:
		//	m_pAnimControl->GetAnimationSet(dwSelect, &pAS);
		//	m_pAnimControl->GetTrackAnimationSet(0, &pASCompare);
		//	if (!strcmp(pAS->GetName(), pASCompare->GetName())) //이미 Idle인 경우.
		//	{
		//		m_pAnimControl->GetTrackDesc(0, &desc);
		//		if (desc.Position + 0.2 >= pAS->GetPeriod())
		//		{
		//			m_State = IDLE;
		//		}
		//	}
		//	else
		//	{
		//		m_pAnimControl->SetTrackAnimationSet(0, pAS);
		//		m_pAnimControl->SetTrackPosition(0, 0);
		//	}

		//	break;
	}

	UpdateSkinnedMesh(m_pFrameRoot);
	//LPD3DXANIMATIONSET pAS;
	//D3DXTRACK_DESC test;

	//m_pAnimControl->GetTrackDesc(dwCurr, &test);
	//a = test.Position;
	//m_pAnimControl->GetAnimationSet(3, &pAS);
	//if (test.Position > pAS->GetPeriod())
	//{
	//	/*m_pAnimControl->SetTrackEnable(0, TRUE);*/
	//	m_pAnimControl->GetAnimationSet(1, &pAS);
	//	m_pAnimControl->SetTrackAnimationSet(0, pAS);
	//	/*m_pAnimControl->SetTrackEnable(1, FALSE);*/
	//}
}


void cXLoader::Render()
{
	/*for (DWORD i = 0; i < m_NumMtl; i++)
	{
	g_pD3DDevice->SetMaterial(&m_pMtl[i]);
	g_pD3DDevice->SetTexture(0, m_pTexture[i]);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEXT::FVF);
	m_pMesh->DrawSubset(i);
	}*/

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->LightEnable(0, true);
	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//D3DXMatrixIdentity(&m_pFrame->TransformationMatrix);
	ST_BONE* pBone = (ST_BONE*)m_pFrameRoot;
	RecursiveFrameRender(pBone, &pBone->matWorldTM);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//g_pD3DDevice->SetTexture(0, nullptr);

}

void cXLoader::SetupWorldMatrix(D3DXFRAME * pFrame, D3DXMATRIXA16 * pmatParent)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	pBone->matWorldTM = pBone->TransformationMatrix;

	if (pmatParent)
	{
		pBone->matWorldTM *= (*pmatParent);
	}

	if (pBone->pFrameSibling)
	{
		SetupWorldMatrix(pBone->pFrameSibling, pmatParent);
	}
	if (pBone->pFrameFirstChild)
	{
		SetupWorldMatrix(pBone->pFrameFirstChild, &pBone->matWorldTM);
	}
}

void cXLoader::SetupBoneMatrixPtrs(D3DXFRAME * pFrame)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;

	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.

	// pSkinInfo->GetNumBones() 으로 영향받는 본의 개수를 찾음.
	// pSkinInfo->GetBoneName(i) 로 i번 프레임의 이름을 찾음
	// D3DXFrameFind(루트 프레임, 프레임 이름) 로 프레임을 찾음.
	// 찾아서 월드매트릭스를 걸어줘라.

	//재귀적으로 모든 프레임에 대해서 실행.
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
{// pCurrentBoneMatrices 를 계산하시오
 // pCurrentBoneMatrices = pBoneOffsetMatrices * ppBoneMatrixPtrs 

 // 	BYTE* src = NULL;
 // 	BYTE* dest = NULL;
 // 
 // 	pBoneMesh->pOrigMesh->LockVertexBuffer( D3DLOCK_READONLY, (void**)&src );
 // 	pBoneMesh->MeshData.pMesh->LockVertexBuffer( 0, (void**)&dest );
 // 
 // 	//MeshData.pMesh을 업데이트 시켜준다.
 // 	pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
 // 		pBoneMesh->pCurrentBoneMatrices, NULL, src, dest );
 // 
 // 	pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
 // 	pBoneMesh->pOrigMesh->UnlockVertexBuffer();

 //재귀적으로 모든 프레임에 대해서 실행

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

		//MeshData.pMesh을 업데이트 시켜준다.
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

void cXLoader::RecursiveFrameRender(D3DXFRAME * pParent, D3DXMATRIXA16 * pParentWorldTM)
{
	ST_BONE* pBone = (ST_BONE*)pParent;
	D3DXMATRIXA16 matW;
	D3DXMatrixIdentity(&matW);

	matW = pParent->TransformationMatrix * (*pParentWorldTM);

	D3DXMATRIXA16 matWorld, matS, matT; D3DXMatrixIdentity(&matS); D3DXMatrixIdentity(&matT);
	D3DXMatrixScaling(&matS, 0.03f, 0.03f, 0.03f);
	D3DXMatrixTranslation(&matT, 0, 0, 0);
	matWorld = matS*matT;
	pBone->matWorldTM = matW;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	//m_pMesh->DrawSubset(0);//렌더
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
	//자식
	if (pParent->pFrameFirstChild)
	{
		RecursiveFrameRender(pParent->pFrameFirstChild, &pBone->matWorldTM);
	}
	//형제
	if (pParent->pFrameSibling)
	{
		RecursiveFrameRender(pParent->pFrameSibling, pParentWorldTM);
	}
}

cXLoader::~cXLoader()
{
	D3DXFrameDestroy(m_pFrameRoot, m_pAlloc);
	//m_pAlloc->DestroyFrame(m_pFrame);
	SAFE_DELETE(m_pAlloc);
	SAFE_RELEASE(m_pMesh);

	SAFE_DELETE(m_pMtl);
	for (DWORD i = 0; i < m_NumMtl; i++)
	{
		SAFE_DELETE(m_pTexture[i]);

	}
	/*m_pMesh->Release();*/
}

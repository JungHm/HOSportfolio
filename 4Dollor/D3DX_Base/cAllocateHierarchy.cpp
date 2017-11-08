#include "stdafx.h"
#include "cAllocateHierarchy.h"


cAllocateHierarchy::cAllocateHierarchy()
{
}


cAllocateHierarchy::~cAllocateHierarchy()
{
}

HRESULT cAllocateHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME * ppNewFrame)
{
	HRESULT hr = S_OK;
	D3DXFRAME_DERIVED *pFrame;     //만들 프레임노드
	
	*ppNewFrame = NULL;
	pFrame = new D3DXFRAME_DERIVED;    //부모의 변황행렬을 가지는 D3DXFRAME_DERIVED 클래스를 할당
	if (pFrame == NULL)
	{
		hr = E_OUTOFMEMORY;
		goto e_Exit;
	}
	hr = AllocateName(Name, &pFrame->Name);  //이름을 할당(멀티바이트형으로)
	if (FAILED(hr))
		goto e_Exit;
	// initialize other data members of the frame
	D3DXMatrixIdentity(&pFrame->TransformationMatrix);   //로컬 변환행렬을 초기화
	D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix); //부모의 변황행렬들을 초기화
															   //모든 연결포인터들을 일단 NULL로
	pFrame->pMeshContainer = NULL;
	pFrame->pFrameSibling = NULL;
	pFrame->pFrameFirstChild = NULL;
	*ppNewFrame = pFrame;          //만들어진 프레임노드를 건내주고
	pFrame = NULL;            //자신은 널
e_Exit:               //실패시 처리
	delete pFrame;

	return hr;


}

HRESULT cAllocateHierarchy::CreateMeshContainer(LPCSTR Name, CONST D3DXMESHDATA * pMeshData, CONST D3DXMATERIAL * pMaterials, CONST D3DXEFFECTINSTANCE * pEffectInstances, DWORD NumMaterials, CONST DWORD * pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER * ppNewMeshContainer)
{
	return E_NOTIMPL;
}

HRESULT cAllocateHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	return E_NOTIMPL;
}

HRESULT cAllocateHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
{
	return E_NOTIMPL;
}

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
	D3DXFRAME_DERIVED *pFrame;     //���� �����ӳ��
	
	*ppNewFrame = NULL;
	pFrame = new D3DXFRAME_DERIVED;    //�θ��� ��Ȳ����� ������ D3DXFRAME_DERIVED Ŭ������ �Ҵ�
	if (pFrame == NULL)
	{
		hr = E_OUTOFMEMORY;
		goto e_Exit;
	}
	hr = AllocateName(Name, &pFrame->Name);  //�̸��� �Ҵ�(��Ƽ����Ʈ������)
	if (FAILED(hr))
		goto e_Exit;
	// initialize other data members of the frame
	D3DXMatrixIdentity(&pFrame->TransformationMatrix);   //���� ��ȯ����� �ʱ�ȭ
	D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix); //�θ��� ��Ȳ��ĵ��� �ʱ�ȭ
															   //��� ���������͵��� �ϴ� NULL��
	pFrame->pMeshContainer = NULL;
	pFrame->pFrameSibling = NULL;
	pFrame->pFrameFirstChild = NULL;
	*ppNewFrame = pFrame;          //������� �����ӳ�带 �ǳ��ְ�
	pFrame = NULL;            //�ڽ��� ��
e_Exit:               //���н� ó��
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

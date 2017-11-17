#pragma once

using namespace std;
class cMtlTex;
struct ST_BONE : public D3DXFRAME
{
	MATRIX16_FIX;
	D3DXMATRIXA16 matWorldTM; //�� Bone�� ���� ��Ʈ����. D3DXFRAME�ȿ��� ��ȯ��Ʈ����(Local?)�� ����.
};

struct ST_BONE_MESH : public D3DXMESHCONTAINER
{
	DWORD					numSubset; //�޽��� �̷�� ������ ���� ������ �ٸ���� ���� ������ ����ϴ� ������ ���� set�� ��� ������ ��������.
	std::vector<cMtlTex*>	vecMtlTex; //������ ������ �����ϴ� �ؽ��ĸ� ����ִ� cMtlTex Ŭ������ ���� ������ŭ ����. ���ͷ� ����.
	LPD3DXMESH				pOrigMesh; //���� �޽�
	D3DXMATRIX**			ppBoneMatrixPtrs; // �� �޽��� ������ �ִ� �����ӵ��� �����Ʈ���� ������ '�迭'
	D3DXMATRIXA16*			pBoneOffsetMatrices; //���� �޽��� ���ý����̽��� ������ ��Ʈ������? NodeTM�����?
	D3DXMATRIXA16*          pCurrentBoneMatrices;	// �� ���� ���� �����Ʈ����
};

class cAllocateHierarchy : public ID3DXAllocateHierarchy
{
public:
	
	cAllocateHierarchy();
	~cAllocateHierarchy();

	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame) override;

	STDMETHOD(CreateMeshContainer(
		THIS_ LPCSTR Name,
		CONST D3DXMESHDATA* pMeshData,
		CONST D3DXMATERIAL* pMaterials,
		CONST D3DXEFFECTINSTANCE* pEffectInstance,
		DWORD NumMaterials,
		CONST DWORD* pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER* ppNewMeshContainer));

	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);

	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree);

};


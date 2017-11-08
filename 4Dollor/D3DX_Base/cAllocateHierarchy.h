#pragma once
struct D3DXFRAME_DERIVED : public D3DXFRAME    //�����ӳ��κ��� ��ӹ޵� �θ��� ��ȯ��ĵ��� ������ �ȴ�
{
	D3DXMATRIXA16        CombinedTransformationMatrix; //������ �θ���� ��ȯ���
};
struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER //�޽� �����̳ʷκ��� ��ӹް�, �ؽ���, �Ӽ����̺�, ������ ����� ������
{
	LPDIRECT3DTEXTURE9*  ppTextures;       // array of textures, entries are NULL if no texture specified   
										   // SkinMesh info             
	LPD3DXMESH           pOrigMesh;    //���� �޽�
	LPD3DXATTRIBUTERANGE pAttributeTable;  //�Ӽ� ���̺�
	DWORD                NumAttributeGroups; //�Ӽ� �׷��� ��
	DWORD                NumInfl;    //�� ����̽��� �����Ҽ� �ִ� �ִ� ����
	LPD3DXBUFFER         pBoneCombinationBuf; //�� �޺���̼� ����
	D3DXMATRIX**         ppBoneMatrixPtrs;  //�����ӿ� �����Ǿ��ִ� ��ȯ ��Ʈ�����迭���� ������
	D3DXMATRIX*          pBoneOffsetMatrices; //���� ��ġ�� ��Ƶ� ��Ʈ���� �迭�� ������
	DWORD                NumPaletteEntries;  //��� �ȷ�Ʈ ��Ʈ��(nonindexed���� ���ȵ�)
	bool                 UseSoftwareVP;   //����Ʈ���� ���ؽ� ���μ����� ����ϴ°�
	DWORD                iAttributeSW;     // used to denote the split between SW and HW if necessary for non-indexed skinning
};
class cAllocateHierarchy : public ID3DXAllocateHierarchy
{
public:
	cAllocateHierarchy();
	~cAllocateHierarchy();

	HRESULT CreateFrame(LPCSTR Name, LPD3DXFRAME *ppNewFrame);
	HRESULT CreateMeshContainer(
		LPCSTR Name,           //�޽� �����̳��� �̸�
		CONST D3DXMESHDATA *pMeshData,       //�޽� ������
		CONST D3DXMATERIAL *pMaterials,       //���� ����
		CONST D3DXEFFECTINSTANCE *pEffectInstances,    //����Ʈ
		DWORD NumMaterials,          //���� ��
		CONST DWORD *pAdjacency,        //�������� ������
		LPD3DXSKININFO pSkinInfo,        //��Ű������
		LPD3DXMESHCONTAINER *ppNewMeshContainer);    //��ȯ�� �޽������̳��� �ּ�

	HRESULT DestroyFrame(LPD3DXFRAME pFrameToFree);
	HRESULT DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase);
};
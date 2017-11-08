#pragma once
struct D3DXFRAME_DERIVED : public D3DXFRAME    //프레임노드로부터 상속받되 부모의 변환행렬들을 가지게 된다
{
	D3DXMATRIXA16        CombinedTransformationMatrix; //축적된 부모들의 변환행렬
};
struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER //메시 컨테이너로부터 상속받고, 텍스쳐, 속성테이블, 뼈결합 등등을 가진다
{
	LPDIRECT3DTEXTURE9*  ppTextures;       // array of textures, entries are NULL if no texture specified   
										   // SkinMesh info             
	LPD3DXMESH           pOrigMesh;    //원본 메시
	LPD3DXATTRIBUTERANGE pAttributeTable;  //속성 테이블
	DWORD                NumAttributeGroups; //속성 그룹의 수
	DWORD                NumInfl;    //이 디바이스가 블랜딩할수 있는 최대 갯수
	LPD3DXBUFFER         pBoneCombinationBuf; //본 콤비네이션 버퍼
	D3DXMATRIX**         ppBoneMatrixPtrs;  //프레임에 저정되어있는 변환 매트릭스배열들의 포인터
	D3DXMATRIX*          pBoneOffsetMatrices; //본의 위치를 담아둘 매트릭스 배열의 포인터
	DWORD                NumPaletteEntries;  //행렬 팔레트 엔트리(nonindexed에선 사용안됨)
	bool                 UseSoftwareVP;   //소프트웨어 버텍스 프로세싱을 사용하는가
	DWORD                iAttributeSW;     // used to denote the split between SW and HW if necessary for non-indexed skinning
};
class cAllocateHierarchy : public ID3DXAllocateHierarchy
{
public:
	cAllocateHierarchy();
	~cAllocateHierarchy();

	HRESULT CreateFrame(LPCSTR Name, LPD3DXFRAME *ppNewFrame);
	HRESULT CreateMeshContainer(
		LPCSTR Name,           //메시 컨테이너의 이름
		CONST D3DXMESHDATA *pMeshData,       //메시 데이터
		CONST D3DXMATERIAL *pMaterials,       //재질 정보
		CONST D3DXEFFECTINSTANCE *pEffectInstances,    //이펙트
		DWORD NumMaterials,          //재질 수
		CONST DWORD *pAdjacency,        //인접정보 포인터
		LPD3DXSKININFO pSkinInfo,        //스키닝정보
		LPD3DXMESHCONTAINER *ppNewMeshContainer);    //반환할 메시컨테이너의 주소

	HRESULT DestroyFrame(LPD3DXFRAME pFrameToFree);
	HRESULT DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase);
};
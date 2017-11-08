#pragma once
class cXLoader
{
private:
	LPD3DXMESH m_pMesh;
	D3DMATERIAL9* m_pMeshMtl;
	LPDIRECT3DTEXTURE9* m_pMeshTexture;
	DWORD	m_dwNum;

	LPD3DXANIMATIONCONTROLLER m_pAnimation;
	LPD3DXALLOCATEHIERARCHY m_pAlloc;
	LPD3DXFRAME m_pFrame;
	//ID3DXAnimationController
public:
	cXLoader();
	~cXLoader();

	void Load(char* fileName);

	void Render();
};


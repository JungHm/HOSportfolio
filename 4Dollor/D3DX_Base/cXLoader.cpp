#include "stdafx.h"
#include "cXLoader.h"



cXLoader::cXLoader()
{
}


cXLoader::~cXLoader()
{
}

void cXLoader::Load(char* fileName)
{
	/*struct tagFrame : public D3DXFRAME
	{
		D3DXMATRIXA16 worldTM;
	};
	struct tagmeshcontainder : public D3DXMESHCONTAINER
	{
		d
	};
	ID3DXAllocateHierarchy	*/
	LPD3DXBUFFER pD3dxMtrlBuffer;
	DWORD dwNumMaterials;
	
		////애니메이션 정보
	D3DXLoadMeshHierarchyFromX(L"fire/fire.x", 
		D3DXMESH_MANAGED, g_pD3DDevice,
		m_pAlloc, NULL, &m_pFrame, &m_pAnimation);
	//메쉬 정보
	D3DXLoadMeshFromX(L"Tiny/tiny.x", D3DXMESH_SYSTEMMEM, g_pD3DDevice, NULL,
		&pD3dxMtrlBuffer, NULL, &m_dwNum, &m_pMesh);

	//ID3DXAnimationSet* Idle = nullptr;
	//m_pAnimation->GetAnimationSet(0, &Idle);
	//m_pAnimation->SetTrackAnimationSet(0, Idle);
	//m_pAnimation->SetTrackEnable(0, TRUE);
	//m_pAnimation->ResetTime();
	////Animation LOAD End

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3dxMtrlBuffer->GetBufferPointer();
	m_pMeshMtl = new D3DMATERIAL9[m_dwNum];
	m_pMeshTexture = new LPDIRECT3DTEXTURE9[m_dwNum];

	for (DWORD i = 0; i < m_dwNum; i++)
	{
		m_pMeshMtl[i] = d3dxMaterials[i].MatD3D;
		//Set the ambient color for the material (D3DX does not do this)
		m_pMeshMtl[i].Ambient = m_pMeshMtl[i].Diffuse;

		m_pMeshTexture[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL &&
			strlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			std::string file = d3dxMaterials[i].pTextureFilename;
			char* szbuf = "fefefefef";
			std::string s(szbuf, szbuf + strlen(szbuf));
			std::wstring ws(file.begin(), file.end());
			
			D3DXCreateTextureFromFile(g_pD3DDevice, ws.c_str(),
				&m_pMeshTexture[i]);
		}
	}

	pD3dxMtrlBuffer->Release();

}

void cXLoader::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixScaling(&matWorld, 0.01f, 0.01f, 0.01f);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	for (DWORD i = 0; i < m_dwNum; i++)
	{
		g_pD3DDevice->SetMaterial(&m_pMeshMtl[i]);
		g_pD3DDevice->SetTexture(0, m_pMeshTexture[i]);

		m_pMesh->DrawSubset(i);
	}
}

#pragma once

class cHeightMap
{
private:
	D3DXMATRIXA16		   m_matWorld;
	LPD3DXMESH			   m_pMesh;
	D3DMATERIAL9		   m_mtl;
	LPDIRECT3DTEXTURE9	   m_pTexture;
	vector<ST_PNT_VERTEXT> m_vecVertex;
	int					   m_nRow;

public:
	cHeightMap();
	~cHeightMap();

	void Setup(char* szFolder, char* szRow, char* szTexture);
	void Render();
};


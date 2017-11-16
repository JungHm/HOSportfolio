#include "stdafx.h"
#include "cTextureManager.h"


cTextureManager::cTextureManager()
{
}


cTextureManager::~cTextureManager()
{
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(std::string sFullPath)
{
	char* szbuf = "fefefefef";
	std::string s(szbuf, szbuf + strlen(szbuf));
	std::wstring ws(sFullPath.begin(), sFullPath.end());
	if (m_mapTexture.find(sFullPath) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFile(g_pD3DDevice,
			ws.c_str(),
			&m_mapTexture[sFullPath]);
	}
	return m_mapTexture[sFullPath];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(char * szFullPath)
{
	return GetTexture(std::string(szFullPath));
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(string sFullPath, D3DXIMAGE_INFO * pImageInfo)
{
	wstring ws(sFullPath.begin(), sFullPath.end());

	if (m_mapTexture.find(sFullPath) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			ws.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			D3DCOLOR_XRGB(255, 255, 255),
			&m_mapImageInfo[sFullPath],
			NULL,
			&m_mapTexture[sFullPath]);
	}
	*pImageInfo = m_mapImageInfo[sFullPath];

	return m_mapTexture[sFullPath];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(char * szFullPath, D3DXIMAGE_INFO * pImageInfo)
{
	return GetTexture(string(szFullPath), pImageInfo);
}

void cTextureManager::Destroy()
{
	for each(auto p in m_mapTexture)
	{
		SAFE_RELEASE(p.second);
	}
	m_mapTexture.clear();
}

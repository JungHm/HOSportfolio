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

void cTextureManager::Destroy()
{
	for each(auto p in m_mapTexture)
	{
		SAFE_RELEASE(p.second);
	}
	m_mapTexture.clear();
}

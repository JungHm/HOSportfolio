#include "stdafx.h"
#include "cXFileManager.h"


cXFileManager::cXFileManager()
{
}


cXFileManager::~cXFileManager()
{
}

void cXFileManager::Destroy()
{
	for each(auto p in m_pXFile)
	{
		p.second->Destroy();
		SAFE_DELETE(p.second);
	}
	m_pXFile.clear();
}

void cXFileManager::KeyDestroy(int key)
{
	m_pXFile[key]->Destroy();
	SAFE_DELETE(m_pXFile[key]);
}

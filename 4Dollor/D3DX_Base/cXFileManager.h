#pragma once
#include "cXLoader.h"

#define XFile cXFileManager::GetInstance()

class cXFileManager
{
private:
	std::map<int, cXLoader*> m_pXFile;
	std::map<int, std::wstring> m_pPath;
public:
	SINGLETONE(cXFileManager);

	cXLoader* GetXFile(int key) { return m_pXFile[key]; }
	void SetXFile(int key, std::wstring path) {
		for each(auto p in m_pPath)
		{
			if (!wcscmp(p.second.c_str(), path.c_str()))
			{
				m_pXFile[key] = m_pXFile[p.first];
				return;
			}
		}
		m_pPath[key] = path;
		m_pXFile[key] = new cXLoader;
		m_pXFile[key]->XfileLoad(path);
	}
	LPD3DXANIMATIONCONTROLLER GetAniCtrl(int key) { return m_pXFile[key]->getAnimCtrl(); }

	void Destroy();
	void KeyDestroy(int key);
};


#pragma once
#define g_pFontManager	cFontManager::GetInstance()

class cFontManager
{
private:
	SINGLETONE(cFontManager);
	std::map<eFontType, LPD3DXFONT>	m_mapFont;

public:
	LPD3DXFONT GetFont(IN eFontType e, IN int nWidth, IN int nHeight);
	void Destroy();
};


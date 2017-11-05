#pragma once
#define g_pFontManager	cFontManager::GetInstance()

class cFontManager
{
private:
	SINGLETONE(cFontManager);
	std::map<eFontType, LPD3DXFONT>	m_mapFont;

public:
	//cFontManager();
	//~cFontManager();
	LPD3DXFONT	GetFont(eFontType e);
	void Destroy();

};


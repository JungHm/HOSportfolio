#pragma once
#define g_pFontManager	cFontManager::GetInstance()

class cFontManager
{

public:
	enum eFontType
	{
		FT_DEFAULT,
		FT_QUEST,
		FT_SMALL
	};
	SINGLETONE(cFontManager);

private:
	std::map<eFontType, LPD3DXFONT>	m_mapFont;

public:
	//cFontManager();
	//~cFontManager();
	LPD3DXFONT	GetFont(eFontType e);
	void Destroy();

};


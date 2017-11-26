#include "stdafx.h"
#include "cFontManager.h"


cFontManager::cFontManager()
{
}


cFontManager::~cFontManager()
{
}

LPD3DXFONT cFontManager::GetFont(eFontType e)
{
	if (m_mapFont.find(e) != m_mapFont.end())
	{
		return m_mapFont[e];
	}


	// font
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));

	if (e == FT_DEFAULT)
	{
		fd.Height = 25;
		fd.Width = 12;
		fd.Weight = FW_BOLD;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
	}
	else if (e == FT_QUEST)
	{
		fd.Height = 50;
		fd.Width = 25;
		fd.Weight = FW_MEDIUM;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;

		AddFontResource(L"font/koKR_bold.ttf");
	}
	else if (e == FT_SMALL)
	{
		fd.Height = 30;
		fd.Width = 12;
		fd.Weight = FW_BOLD;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;

		AddFontResource(L"font/koKR_bold.ttf");
	}

	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[e]);

	return m_mapFont[e];
}

void cFontManager::Destroy()
{
	for each (auto it in m_mapFont)
	{
		SAFE_RELEASE(it.second);
	}
}

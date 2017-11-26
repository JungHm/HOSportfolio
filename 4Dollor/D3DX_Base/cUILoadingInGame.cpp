#include "stdafx.h"
#include "cUILoadingInGame.h"


cUILoadingInGame::cUILoadingInGame()
	: m_LoadingEnd(false)
{
}


cUILoadingInGame::~cUILoadingInGame()
{
}

int cUILoadingInGame::updateButtonOverCallback(int num)
{
	return 0;
}

int cUILoadingInGame::updateButtonCallback(int num)
{
	m_LoadingEnd = true;
	return 0;
}

void cUILoadingInGame::setupOther()
{
}

void cUILoadingInGame::updateOther()
{
}

void cUILoadingInGame::renderOther()
{
	LPD3DXFONT font = g_pFontManager->GetFont(cFontManager::FT_QUEST);
	string str = "Loading...";
	RECT rcText;
	SetRect(&rcText, WINX - 500, WINY - 500, WINX - 50, WINY - 80);
	font->DrawTextA(NULL, str.c_str(), str.length(), &rcText, DT_RIGHT | DT_BOTTOM, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void cUILoadingInGame::destroyOther()
{
}

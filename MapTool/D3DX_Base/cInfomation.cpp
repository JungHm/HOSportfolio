#include "stdafx.h"
#include "cInfomation.h"

cInfomation::cInfomation()
	: m_pFont(NULL)
{
}

cInfomation::~cInfomation()
{
	SAFE_RELEASE(m_pFont);
}

void cInfomation::Setup()
{
	m_pFont = g_pFontManager->GetFont(FT_QUEST, 7, 12);
}

void cInfomation::Render()
{
	char szWolrdTime[1024];
	sprintf_s(szWolrdTime, "WorldTime : %.2f", g_pTimeManager->GetWorldTime());

	RECT rc;
	SetRect(&rc, 0, 0, 10, 20);
	m_pFont->DrawTextA(NULL, szWolrdTime, strlen(szWolrdTime), &rc,DT_LEFT | DT_TOP | DT_NOCLIP,D3DCOLOR_XRGB(255, 255, 255));
}

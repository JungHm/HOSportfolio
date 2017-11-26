#include "stdafx.h"
#include "cUILoadingClientBegin.h"


cUILoadingClientBegin::cUILoadingClientBegin()
	: m_LoadingEnd(false)
{
}

cUILoadingClientBegin::~cUILoadingClientBegin()
{
}

int cUILoadingClientBegin::updateButtonOverCallback(int num)
{
	return 0;
}

int cUILoadingClientBegin::updateButtonCallback(int num)
{
	m_LoadingEnd = true;
	return 0;
}

void cUILoadingClientBegin::setupOther()
{
}

void cUILoadingClientBegin::updateOther()
{
}

void cUILoadingClientBegin::renderOther()
{
	tagUISpriteButton *info = &m_MUIButton.find("l1")->second;
	LPD3DXFONT font = g_pFontManager->GetFont(cFontManager::FT_SMALL);
	string str = "게임 시작";
	RECT rcText;
	SetRect(&rcText, info->pt.x, info->pt.y, info->pt.x + info->imgInfo.Width * m_UIScale, info->pt.y + info->imgInfo.Height * m_UIScale);
	font->DrawTextA(NULL, str.c_str(), str.length(), &rcText, DT_CENTER | DT_VCENTER, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void cUILoadingClientBegin::destroyOther()
{
}

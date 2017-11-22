#include "stdafx.h"
#include "cUIMainMenu.h"


cUIMainMenu::cUIMainMenu()
	: m_GameStart(false)
{
}


cUIMainMenu::~cUIMainMenu()
{
}

int cUIMainMenu::updateButtonCallback(int num)
{
	if (num == UIBUTTONCALLBACK_MAIN_READY)
	{
		m_GameStart = true;
	}
	else if (num == UIBUTTONCALLBACK_MAIN_HEROINFO_ABILITY)
	{

	}
	else if (num == UIBUTTONCALLBACK_MAIN_HEROINFO_EQUIP)
	{

	}
	else if (num == UIBUTTONCALLBACK_MAIN_HEROINFO_TALENT)
	{

	}
	else if (num == UIBUTTONCALLBACK_MAIN_HEROSELECT_ROLE)
	{

	}
	else if (num == UIBUTTONCALLBACK_MAIN_HEROSELECT_GAME)
	{

	}
	else if (num == UIBUTTONCALLBACK_MAIN_HEROSELECT_HERO)
	{

	}
	return 0;
}

int cUIMainMenu::updateButtonOverCallback(int num)
{
	if (num == UIBUTTONCALLBACK_MAIN_READY)
	{
		
	}
	else if (num == UIBUTTONCALLBACK_MAIN_HEROINFO_ABILITY)
	{

	}
	else if (num == UIBUTTONCALLBACK_MAIN_HEROINFO_EQUIP)
	{

	}
	else if (num == UIBUTTONCALLBACK_MAIN_HEROINFO_TALENT)
	{

	}
	else if (num == UIBUTTONCALLBACK_MAIN_HEROSELECT_ROLE)
	{

	}
	else if (num == UIBUTTONCALLBACK_MAIN_HEROSELECT_GAME)
	{

	}
	else if (num == UIBUTTONCALLBACK_MAIN_HEROSELECT_HERO)
	{

	}
	return 0;
}

void cUIMainMenu::setupOther()
{
	POINT rcSizeReady = { m_MUIButton.find("ready")->second.imgInfo.Width * m_UIScale, m_MUIButton.find("ready")->second.imgInfo.Height * m_UIScale };
	POINT ptReady = { m_MUIButton.find("ready")->second.pt.x, m_MUIButton.find("ready")->second.pt.y };
	POINT rcSizeHeroinfo = { m_MUIButton.find("heroinfo")->second.imgInfo.Width * m_UIScale, m_MUIButton.find("heroinfo")->second.imgInfo.Height * m_UIScale * 2 };
	POINT ptHeroinfo = { m_MUIButton.find("heroinfo")->second.pt.x, m_MUIButton.find("heroinfo")->second.pt.y };
	POINT rcSizeAbility = { m_MUIButton.find("heroabil")->second.imgInfo.Width * m_UIScale, m_MUIButton.find("heroabil")->second.imgInfo.Height * m_UIScale * 2 };
	POINT ptAbility = { m_MUIButton.find("heroabil")->second.pt.x, m_MUIButton.find("heroabil")->second.pt.y };
	POINT rcSizeTalent = { m_MUIButton.find("herotalent")->second.imgInfo.Width * m_UIScale, m_MUIButton.find("herotalent")->second.imgInfo.Height * m_UIScale * 2 };
	POINT ptTalent = { m_MUIButton.find("herotalent")->second.pt.x, m_MUIButton.find("herotalent")->second.pt.y };

	setupTextInput("장비", cFontManager::FT_SMALL, ptHeroinfo, rcSizeHeroinfo);
	setupTextInput("기술", cFontManager::FT_SMALL, ptAbility, rcSizeAbility);
	setupTextInput("특성", cFontManager::FT_SMALL, ptTalent, rcSizeTalent);
	setupTextInput("준비", cFontManager::FT_SMALL, ptReady, rcSizeReady);
}

void cUIMainMenu::setupTextInput(string strName, cFontManager::eFontType fontType, POINT pt, POINT rcPt)
{
	tagTextView tv;
	tv.alpha = 255;
	tv.pt = pt;
	tv.str = strName;
	SetRect(&tv.rcText, tv.pt.x, tv.pt.y, tv.pt.x + rcPt.x, tv.pt.y + rcPt.y);
	m_VText.push_back(tv);
}

void cUIMainMenu::updateOther()
{
}

void cUIMainMenu::renderOther()
{
	for each(auto p in m_VText)
	{
		LPD3DXFONT font = g_pFontManager->GetFont(cFontManager::FT_SMALL);
		font->DrawTextA(NULL, p.str.c_str(), p.str.length(), &p.rcText, DT_CENTER | DT_VCENTER, D3DCOLOR_ARGB(p.alpha, 255, 255, 255));
	}
}

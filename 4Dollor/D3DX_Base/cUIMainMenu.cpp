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
		if (!m_MUIButton.find("heroabil")->second.selected)
		{
			m_MUIButton.find("heroabil")->second.selected = true;
			m_MUIButton.find("heroinfo")->second.selected = false;
			m_MUIButton.find("herotalent")->second.selected = false;
		}
		else
		{
			m_MUIButton.find("heroabil")->second.selected = false;
		}
	}
	else if (num == UIBUTTONCALLBACK_MAIN_HEROINFO_EQUIP)
	{
		if (!m_MUIButton.find("heroinfo")->second.selected)
		{
			m_MUIButton.find("heroabil")->second.selected = false;
			m_MUIButton.find("heroinfo")->second.selected = true;
			m_MUIButton.find("herotalent")->second.selected = false;
		}
		else
		{
			m_MUIButton.find("heroinfo")->second.selected = false;
		}
	}
	else if (num == UIBUTTONCALLBACK_MAIN_HEROINFO_TALENT)
	{
		if (!m_MUIButton.find("herotalent")->second.selected)
		{
			m_MUIButton.find("heroabil")->second.selected = false;
			m_MUIButton.find("heroinfo")->second.selected = false;
			m_MUIButton.find("herotalent")->second.selected = true;
		}
		else
		{
			m_MUIButton.find("herotalent")->second.selected = false;
		}
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
		if (!m_MUIButton.find("heroabil")->second.selected)
		{
			// 마우스 오버 시 띄울 스킬 설명들
			
		}
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

	setupTextInput("장비", ptHeroinfo, rcSizeHeroinfo);
	setupTextInput("기술", ptAbility, rcSizeAbility);
	setupTextInput("특성", ptTalent, rcSizeTalent);
	setupTextInput("준비", ptReady, rcSizeReady);
}

void cUIMainMenu::setupTextInput(string strName, POINT pt, POINT rcPt)
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
		// 동적할당 해제 안되었다는 오류남
		LPD3DXFONT font = g_pFontManager->GetFont(cFontManager::FT_SMALL);
		font->DrawTextA(NULL, p.str.c_str(), p.str.length(), &p.rcText, DT_CENTER | DT_VCENTER, D3DCOLOR_ARGB(p.alpha, 255, 255, 255));
	}
}

void cUIMainMenu::destroyOther()
{
}

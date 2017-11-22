#include "stdafx.h"
#include "cUIMainMenu.h"


cUIMainMenu::cUIMainMenu()
	: m_GameStart(false)
{
}


cUIMainMenu::~cUIMainMenu()
{
}

void cUIMainMenu::updateButtonCallback(int num)
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
}

void cUIMainMenu::updateButtonOverCallback(int num)
{
	
}

#include "stdafx.h"
#include "cUIInGame.h"


cUIInGame::cUIInGame()
	: m_GameEnd(false)
{
}


cUIInGame::~cUIInGame()
{
}

void cUIInGame::updateButtonOverCallback(int num)
{
}

void cUIInGame::updateButtonCallback(int num)
{
	if (num == UIBUTTONCALLBACK_INGAME_HOME)
	{
		m_GameEnd = true;
	}
}

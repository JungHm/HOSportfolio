#include "stdafx.h"
#include "cUIInGame.h"


cUIInGame::cUIInGame()
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
		g_Scene->ChangeScene("menu");
	}
}

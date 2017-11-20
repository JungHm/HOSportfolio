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

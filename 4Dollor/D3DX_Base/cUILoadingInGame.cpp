#include "stdafx.h"
#include "cUILoadingInGame.h"


cUILoadingInGame::cUILoadingInGame()
	: m_LoadingEnd(false)
{
}


cUILoadingInGame::~cUILoadingInGame()
{
}

void cUILoadingInGame::updateButtonOverCallback(int num)
{
}

void cUILoadingInGame::updateButtonCallback(int num)
{
	m_LoadingEnd = true;
}

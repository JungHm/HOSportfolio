#include "stdafx.h"
#include "cUIInGame.h"


cUIInGame::cUIInGame()
	: m_GameEnd(false)
{
}


cUIInGame::~cUIInGame()
{
}

int cUIInGame::updateButtonOverCallback(int num)
{
	return 0;
}

int cUIInGame::updateButtonCallback(int num)
{
	if (num == UIBUTTONCALLBACK_INGAME_HOME)
	{
		m_GameEnd = true;
	}
	else if (num == UIBUTTONCALLBACK_INGAME_SKILL1)
	{
		SetSkillUse(1, true);	// 스킬이 비활성화, 사용 중이라면 여길 못오니 바로 사용
		return 1;
	}
	else if (num == UIBUTTONCALLBACK_INGAME_SKILL2)
	{
		SetSkillUse(2, true);
		return 2;
	}
	else if (num == UIBUTTONCALLBACK_INGAME_SKILL3)
	{
		SetSkillUse(3, true);
		return 3;
	}
	else if (num == UIBUTTONCALLBACK_INGAME_SKILL4)
	{
		SetSkillUse(4, true);
		return 4;
	}
	else if (num == UIBUTTONCALLBACK_INGAME_SKILL5)
	{
		SetSkillUse(5, true);
		return 5;
	}

	return 0;
}

void cUIInGame::UISetSkillUnlock(int SkillIndex, bool unlock)
{
	if (SkillIndex == 1)
	{
		if (unlock)	// 스킬 언락 시 락 이미지 enable = false & 스킬 enable = true
		{
			m_MUIButton.find("abil1")->second.enable = true;
			m_MUISprite.find("abil1img")->second.enable = true;
			m_MUISprite.find("skill1lock")->second.enable = false;
		}
		else	// 스킬 재사용 가능 시 위에 기능 반대로 작동
		{
			m_MUIButton.find("abil1")->second.enable = false;
			m_MUISprite.find("abil1img")->second.enable = false;
			m_MUISprite.find("skill1lock")->second.enable = true;
		}
	}
	else if (SkillIndex == 2)
	{
		if (unlock)
		{
			m_MUIButton.find("abil2")->second.enable = true;
			m_MUISprite.find("abil2img")->second.enable = true;
			m_MUISprite.find("skil21lock")->second.enable = false;
		}
		else
		{
			m_MUIButton.find("abil2")->second.enable = false;
			m_MUISprite.find("abil2img")->second.enable = false;
			m_MUISprite.find("skil21lock")->second.enable = true;
		}
	}
	else if (SkillIndex == 3)
	{
		if (unlock)
		{
			m_MUIButton.find("abil3")->second.enable = true;
			m_MUISprite.find("abil3img")->second.enable = true;
			m_MUISprite.find("skil31lock")->second.enable = false;
		}
		else
		{
			m_MUIButton.find("abil3")->second.enable = false;
			m_MUISprite.find("abil3img")->second.enable = false;
			m_MUISprite.find("skil31lock")->second.enable = true;
		}
	}
	else if (SkillIndex == 4)
	{
		if (unlock)
		{
			m_MUIButton.find("abil4")->second.enable = true;
			m_MUISprite.find("abil4img")->second.enable = true;
			m_MUISprite.find("skil41lock")->second.enable = false;
		}
		else
		{
			m_MUIButton.find("abil4")->second.enable = false;
			m_MUISprite.find("abil4img")->second.enable = false;
			m_MUISprite.find("skil41lock")->second.enable = true;
		}
	}
	else if (SkillIndex == 5)
	{
		if (unlock)
		{
			m_MUIButton.find("abil5")->second.enable = true;
			m_MUISprite.find("abil5img")->second.enable = true;
			m_MUISprite.find("skil51lock")->second.enable = false;
		}
		else
		{
			m_MUIButton.find("abil5")->second.enable = false;
			m_MUISprite.find("abil5img")->second.enable = false;
			m_MUISprite.find("skil51lock")->second.enable = true;
		}
	}
}

void cUIInGame::UISetSkillUse(int SkillIndex, bool used)
{
	if (SkillIndex == 1)
	{
		if (used)	// 스킬 사용 시 현재 스킬 아이콘을 숨기고 쿨탐 아이콘, Text 표시
		{
			m_MUIButton.find("abil1")->second.used = true;
			m_MUISprite.find("abil1img")->second.enable = false;
		}
		else	// 스킬 재사용 가능 시 위에 기능 반대로 작동
		{
			m_MUIButton.find("abil1")->second.used = false;
			m_MUISprite.find("abil1img")->second.enable = true;
		}
	}
	else if (SkillIndex == 2)
	{
		if (used)
		{
			m_MUIButton.find("abil2")->second.used = true;
			m_MUISprite.find("abil2img")->second.enable = false;
		}
		else
		{
			m_MUIButton.find("abil2")->second.used = false;
			m_MUISprite.find("abil2img")->second.enable = true;
		}
	}
	else if (SkillIndex == 3)
	{
		if (used)
		{
			m_MUIButton.find("abil3")->second.used = true;
			m_MUISprite.find("abil3img")->second.enable = false;
		}
		else
		{
			m_MUIButton.find("abil3")->second.used = false;
			m_MUISprite.find("abil3img")->second.enable = true;
		}
	}
	else if (SkillIndex == 4)
	{
		if (used)
		{
			m_MUIButton.find("abil4")->second.used = true;
			m_MUISprite.find("abil4img")->second.enable = false;
		}
		else
		{
			m_MUIButton.find("abil4")->second.used = false;
			m_MUISprite.find("abil4img")->second.enable = true;
		}
	}
	else if (SkillIndex == 5)
	{
		if (used)
		{
			m_MUIButton.find("abil5")->second.used = true;
			m_MUISprite.find("abil5img")->second.enable = false;
		}
		else
		{
			m_MUIButton.find("abil5")->second.used = false;
			m_MUISprite.find("abil5img")->second.enable = true;
		}
	}
}

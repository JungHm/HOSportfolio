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

void cUIInGame::SetSkillUnlock(int SkillIndex, bool unlock)
{
	string skillName = "abil" + to_string(SkillIndex);
	string skillNameImg = "abil" + to_string(SkillIndex) + "img";
	string skillNameLock = "skill" + to_string(SkillIndex) + "lock";

	if (unlock)	// 스킬 언락 시 락 이미지 enable = false & 스킬 enable = true
	{
		m_MUIButton.find(skillName)->second.enable = true;
		m_MUISprite.find(skillNameImg)->second.enable = true;
		m_MUISprite.find(skillNameLock)->second.enable = false;
	}
	else	// 스킬 재사용 가능 시 위에 기능 반대로 작동
	{
		m_MUIButton.find(skillName)->second.enable = false;
		m_MUISprite.find(skillNameImg)->second.enable = false;
		m_MUISprite.find(skillNameLock)->second.enable = true;
	}
}

void cUIInGame::SetSkillUse(int SkillIndex, bool used)
{
	string skillName = "abil" + to_string(SkillIndex);
	string skillNameImg = "abil" + to_string(SkillIndex) + "img";

	if (used)
	{
		m_MUIButton.find(skillName)->second.used = true;
		m_MUIButton.find(skillName)->second.buttonState = UIBUTTONSTATE_DISENABLE;
		//m_MUISprite.find(skillNameImg)->second.enable = false;
	}
	else
	{
		m_MUIButton.find(skillName)->second.used = false;
		m_MUIButton.find(skillName)->second.buttonState = UIBUTTONSTATE_NORMAL;
		//m_MUISprite.find(skillNameImg)->second.enable = true;
		string countName = "skill" + to_string(SkillIndex) + "cool0";
		m_MUIButton.find(countName)->second.enable = false;
	}
}

void cUIInGame::SetSkillUseCooldown(int SkillIndex, float count)
{
	// 이미지 저장하는 구조부터 바꿔야 할듯. 아래 구조는 불안정하고 확장성이 부족함
	int countInt = (int)count;
	countInt++;	// 0.9가 0으로 치환되므로 표현을 +1로 해준다.
	if (countInt > 9)
		countInt = 9;	// 10초 이상은 구조 자체를 바꿔야 할듯. 지금은 한자리 수만 됨...
	string skillName = "abil" + to_string(SkillIndex);
	string countName = "skill" + to_string(SkillIndex) + "cool" + to_string(countInt);
	string countName2 = "skill" + to_string(SkillIndex) + "cool" + to_string(countInt + 1);

	if (m_MUIButton.find(skillName)->second.used)	// 스킬이 사용 중이라면 카운트 표시. 아니면 안함
	{
		m_MUIButton.find(countName)->second.enable = true;
		if (countInt > 8) return;	// 이게 없으면 countInt + 1 = 10이 될 경우 터짐.
		m_MUIButton.find(countName2)->second.enable = false;
	}
}

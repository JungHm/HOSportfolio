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
		SetSkillUse(1, true);	// ��ų�� ��Ȱ��ȭ, ��� ���̶�� ���� ������ �ٷ� ���
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

	if (unlock)	// ��ų ��� �� �� �̹��� enable = false & ��ų enable = true
	{
		m_MUIButton.find(skillName)->second.enable = true;
		m_MUISprite.find(skillNameImg)->second.enable = true;
		m_MUISprite.find(skillNameLock)->second.enable = false;
	}
	else	// ��ų ���� ���� �� ���� ��� �ݴ�� �۵�
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
	// �̹��� �����ϴ� �������� �ٲ�� �ҵ�. �Ʒ� ������ �Ҿ����ϰ� Ȯ�强�� ������
	int countInt = (int)count;
	countInt++;	// 0.9�� 0���� ġȯ�ǹǷ� ǥ���� +1�� ���ش�.
	if (countInt > 9)
		countInt = 9;	// 10�� �̻��� ���� ��ü�� �ٲ�� �ҵ�. ������ ���ڸ� ���� ��...
	string skillName = "abil" + to_string(SkillIndex);
	string countName = "skill" + to_string(SkillIndex) + "cool" + to_string(countInt);
	string countName2 = "skill" + to_string(SkillIndex) + "cool" + to_string(countInt + 1);

	if (m_MUIButton.find(skillName)->second.used)	// ��ų�� ��� ���̶�� ī��Ʈ ǥ��. �ƴϸ� ����
	{
		m_MUIButton.find(countName)->second.enable = true;
		if (countInt > 8) return;	// �̰� ������ countInt + 1 = 10�� �� ��� ����.
		m_MUIButton.find(countName2)->second.enable = false;
	}
}

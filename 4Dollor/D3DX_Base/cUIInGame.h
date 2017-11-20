#pragma once
#include "cUIObject.h"

class cUIInGame : public cUIObject
{
private:
	// ���� ��ư Ŭ������ �� �ѱ� �� �����.
	SYNTHESIZE(bool, m_GameEnd, GameEnd);

public:
	cUIInGame();
	~cUIInGame();

	int updateButtonOverCallback(int num);
	int updateButtonCallback(int num);

	// ��ų ���. q = 1, w = 2 ����
	void UISetSkillUnlock(int SkillIndex, bool unlock);
	// ��ų ��� ��. q = 1, w = 2 ����
	void UISetSkillUse(int SkillIndex, bool used);
};


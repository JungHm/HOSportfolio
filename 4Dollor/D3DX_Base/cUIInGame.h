#pragma once
#include "cUIObject.h"

#define SKILLCOUNT 5
#define SKILLCOUNTNUM 10

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
	void SetSkillUnlock(int SkillIndex, bool unlock);
	// ��ų ��� ��. q = 1, w = 2 ����
	void SetSkillUse(int SkillIndex, bool used);
	// ��ų ��� ��Ÿ�� ǥ��
	void SetSkillUseCooldown(int SkillIndex, float count);

	void setupOther();
	void updateOther();
	void renderOther();
};


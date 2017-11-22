#pragma once
#include "cUIObject.h"

#define SKILLCOUNT 5
#define SKILLCOUNTNUM 10

class cUIInGame : public cUIObject
{
private:
	// 현재 버튼 클릭으로 씬 넘길 때 사용함.
	SYNTHESIZE(bool, m_GameEnd, GameEnd);

public:
	cUIInGame();
	~cUIInGame();

	int updateButtonOverCallback(int num);
	int updateButtonCallback(int num);

	// 스킬 언락. q = 1, w = 2 순서
	void SetSkillUnlock(int SkillIndex, bool unlock);
	// 스킬 사용 시. q = 1, w = 2 순서
	void SetSkillUse(int SkillIndex, bool used);
	// 스킬 사용 쿨타임 표시
	void SetSkillUseCooldown(int SkillIndex, float count);

	void setupOther();
	void updateOther();
	void renderOther();
};


#pragma once
#include "cUIObject.h"

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
	void UISetSkillUnlock(int SkillIndex, bool unlock);
	// 스킬 사용 시. q = 1, w = 2 순서
	void UISetSkillUse(int SkillIndex, bool used);
};


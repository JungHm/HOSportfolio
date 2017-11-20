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

	void updateButtonOverCallback(int num);
	void updateButtonCallback(int num);
};


#pragma once
#include "cUIObject.h"

class cUIInGame : public cUIObject
{
private:
	SYNTHESIZE(bool, m_GameEnd, GameEnd);

public:
	cUIInGame();
	~cUIInGame();

	void updateButtonOverCallback(int num);
	void updateButtonCallback(int num);
};


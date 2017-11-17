#pragma once
#include "cUIObject.h"

class cUIInGame : public cUIObject
{
public:
	cUIInGame();
	~cUIInGame();

	void updateButtonOverCallback(int num);
	void updateButtonCallback(int num);
};


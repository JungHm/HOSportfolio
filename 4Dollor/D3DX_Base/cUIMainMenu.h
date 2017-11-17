#pragma once
#include "cUIObject.h"
class cUIMainMenu : public cUIObject
{
public:
	cUIMainMenu();
	~cUIMainMenu();

	void updateButtonCallback(int num);
	void updateButtonOverCallback(int num);
};


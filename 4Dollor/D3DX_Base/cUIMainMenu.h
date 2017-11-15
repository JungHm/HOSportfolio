#pragma once
#include "cUIObject.h"
class cUIMainMenu : public cUIObject
{
public:
	cUIMainMenu();
	~cUIMainMenu();

	void updateButtonCallback(UIBUTTONCALLBACK num);
	void updateButtonOverCallback(UIBUTTONCALLBACK num);
};


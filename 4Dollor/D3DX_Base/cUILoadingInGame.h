#pragma once
#include "cUIObject.h"
class cUILoadingInGame : public cUIObject
{
private:

public:
	cUILoadingInGame();
	~cUILoadingInGame();

	SYNTHESIZE(bool, m_LoadingEnd, LoadingEnd);

	void updateButtonOverCallback(int num);
	void updateButtonCallback(int num);
};


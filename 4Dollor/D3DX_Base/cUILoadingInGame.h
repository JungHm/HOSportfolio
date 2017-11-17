#pragma once
#include "cUIObject.h"
class cUILoadingInGame : public cUIObject
{
private:
	bool m_LoadingEnd;

public:
	cUILoadingInGame();
	~cUILoadingInGame();

	void updateButtonOverCallback(int num);
	void updateButtonCallback(int num);

	bool getLoadingEnd() { return m_LoadingEnd; }
};


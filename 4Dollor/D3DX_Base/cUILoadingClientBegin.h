#pragma once
#include "cUIObject.h"
class cUILoadingClientBegin : public cUIObject
{
private:
	bool m_LoadingEnd;

public:
	cUILoadingClientBegin();
	~cUILoadingClientBegin();

	void updateButtonOverCallback(int num);
	void updateButtonCallback(int num);

	bool getLoadingEnd() { return m_LoadingEnd; }
};


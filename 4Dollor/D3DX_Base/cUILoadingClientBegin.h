#pragma once
#include "cUIObject.h"
class cUILoadingClientBegin : public cUIObject
{
private:

public:
	cUILoadingClientBegin();
	~cUILoadingClientBegin();

	SYNTHESIZE(bool, m_LoadingEnd, LoadingEnd);

	void updateButtonOverCallback(int num);
	void updateButtonCallback(int num);
};

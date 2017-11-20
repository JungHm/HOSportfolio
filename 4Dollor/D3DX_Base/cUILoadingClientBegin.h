#pragma once
#include "cUIObject.h"
class cUILoadingClientBegin : public cUIObject
{
private:
	// 로딩이 끝난 것을 체크하기 위한 변수
	SYNTHESIZE(bool, m_LoadingEnd, LoadingEnd);

public:
	cUILoadingClientBegin();
	~cUILoadingClientBegin();

	int updateButtonOverCallback(int num);
	int updateButtonCallback(int num);
};

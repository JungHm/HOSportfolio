#pragma once
#include "cUIObject.h"
class cUILoadingClientBegin : public cUIObject
{
private:
	// �ε��� ���� ���� üũ�ϱ� ���� ����
	SYNTHESIZE(bool, m_LoadingEnd, LoadingEnd);

public:
	cUILoadingClientBegin();
	~cUILoadingClientBegin();

	int updateButtonOverCallback(int num);
	int updateButtonCallback(int num);
};

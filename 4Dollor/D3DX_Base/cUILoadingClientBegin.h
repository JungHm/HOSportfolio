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

	void updateButtonOverCallback(int num);
	void updateButtonCallback(int num);
};

#pragma once
#include "cUIObject.h"
class cUILoadingInGame : public cUIObject
{
private:
	// �ε��� ���� ���� üũ�ϱ� ���� ����
	SYNTHESIZE(bool, m_LoadingEnd, LoadingEnd);

public:
	cUILoadingInGame();
	~cUILoadingInGame();

	void updateButtonOverCallback(int num);
	void updateButtonCallback(int num);
};


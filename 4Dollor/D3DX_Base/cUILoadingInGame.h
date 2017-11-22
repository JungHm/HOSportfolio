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

	int updateButtonOverCallback(int num);
	int updateButtonCallback(int num);

	void setupOther();
	void updateOther();
	void renderOther();
};


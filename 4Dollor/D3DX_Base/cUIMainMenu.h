#pragma once
#include "cUIObject.h"
class cUIMainMenu : public cUIObject
{
private:
	// Ready ��ư Ŭ�� �� ���ӿ� �����ϱ� ���� bool
	SYNTHESIZE(bool, m_GameStart, GameStart);

public:
	cUIMainMenu();
	~cUIMainMenu();

	void updateButtonCallback(int num);
	void updateButtonOverCallback(int num);
};


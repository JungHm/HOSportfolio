#pragma once
#include "cUIObject.h"
class cUIMainMenu : public cUIObject
{
private:
	// Ready 버튼 클릭 시 게임에 진입하기 위한 bool
	SYNTHESIZE(bool, m_GameStart, GameStart);

public:
	cUIMainMenu();
	~cUIMainMenu();

	int updateButtonCallback(int num);
	int updateButtonOverCallback(int num);
};


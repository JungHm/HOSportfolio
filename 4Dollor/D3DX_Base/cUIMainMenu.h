#pragma once
#include "cUIObject.h"

struct tagTextView
{
	string str;
	POINT pt;
	RECT rcText;
	int alpha;	// 텍스트 알파 값. 
};

class cUIMainMenu : public cUIObject
{
private:
	// Ready 버튼 클릭 시 게임에 진입하기 위한 bool
	SYNTHESIZE(bool, m_GameStart, GameStart);
	vector<tagTextView> m_VText;
	LPD3DXFONT m_Font;

public:
	cUIMainMenu();
	~cUIMainMenu();

	int updateButtonCallback(int num);
	int updateButtonOverCallback(int num);

	void setupOther();
	void setupTextInput(string strName, cFontManager::eFontType fontType, POINT pt, POINT rcPt);
	void updateOther();
	void renderOther();
	void destroyOther();
};


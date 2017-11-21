#pragma once
#include "cUIObject.h"

struct tagTextView
{
	string str;
	POINT pt;
	RECT rcText;
	int alpha;	// �ؽ�Ʈ ���� ��. 
};

class cUIMainMenu : public cUIObject
{
private:
	// Ready ��ư Ŭ�� �� ���ӿ� �����ϱ� ���� bool
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


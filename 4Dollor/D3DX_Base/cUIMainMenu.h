#pragma once
#include "cUIObject.h"

#define FADEINSPEED 3	// 값이 낮을수록 느림
#define READYCOUNTSTARTSCALE 4
#define READYCOUNTENDSCALE 1.6

class cUILoadingInGame;

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

	bool m_GameReady;
	int m_GameReadyTime;
	map<wstring, tagUISpriteEfx> m_GameReadyEfx;
	map<wstring, tagUISpriteEfx>::iterator m_GameReadyEfxIt;

	wstring m_GameReadyEfxPath[3];
	tagUISpriteEfx m_Fade;

	cUILoadingInGame* m_InGameLoading;
	bool m_InGameLoadingEnable;

public:
	cUIMainMenu();
	~cUIMainMenu();

	int updateButtonCallback(int num);
	int updateButtonOverCallback(int num);

	void heroinfoPopup(bool enable);
	void heroinfoPopup2(string name, bool enable);

	void setupOther();
	void setupTextInput(string strName, POINT pt, POINT rcPt);
	void setupAddTexture(wstring filePath);
	void setupAddFadeImg(wstring filePath);
	void updateOther();
	void updateGameReady();
	void renderOther();
	void renderGameReady();
	void renderFade();
	void renderIngameLoading();
	void destroyOther();
};


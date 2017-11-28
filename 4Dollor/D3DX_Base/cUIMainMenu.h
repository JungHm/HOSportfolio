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
	tagUISpriteEfx test;

public:
	cUIMainMenu();
	~cUIMainMenu();

	int updateButtonCallback(int num);
	int updateButtonOverCallback(int num);

	// 영웅 스킬 버튼 누르면 뜨는 창 (이미지)
	void heroinfoPopup(bool enable);
	// 영웅 스킬에 마우스 오버 시 뜨는 스킬 설명 팝업
	void heroinfoPopup2(string name, bool enable);

	void setupOther();
	// 텍스트 추가 시 기본 설정
	void setupTextInput(string strName, POINT pt, POINT rcPt);
	// 래디 후 숫자 연출 sprite 추가
	void setupAddTexture(wstring filePath);
	// 페이드인 관련 sprite 추가
	void setupAddFadeImg(wstring filePath);
	void setupTest(wstring filePath);
	void updateOther();
	// 래디 후 연출 update
	void updateGameReady();
	void renderOther();
	// 래디 후 연출 render
	void renderGameReady();
	// 레디 후 연출이 종료되면 fade render
	void renderFade();
	void renderTest();

	// 인게임 로딩을 여기서 띄움
	// 쓰레드를 돌리면 인게임 클래스에서 랜더해야 함
	// 현재는 데이터 로드 중 정지 화면이라 먼저 띄워 놓고 로드 시킴
	void renderIngameLoading();
	void destroyOther();
};


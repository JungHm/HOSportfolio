#pragma once
#include "cUIObject.h"

#define FADEINSPEED 3	// ���� �������� ����
#define READYCOUNTSTARTSCALE 4
#define READYCOUNTENDSCALE 1.6

class cUILoadingInGame;

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

	// ���� ��ų ��ư ������ �ߴ� â (�̹���)
	void heroinfoPopup(bool enable);
	// ���� ��ų�� ���콺 ���� �� �ߴ� ��ų ���� �˾�
	void heroinfoPopup2(string name, bool enable);

	void setupOther();
	// �ؽ�Ʈ �߰� �� �⺻ ����
	void setupTextInput(string strName, POINT pt, POINT rcPt);
	// ���� �� ���� ���� sprite �߰�
	void setupAddTexture(wstring filePath);
	// ���̵��� ���� sprite �߰�
	void setupAddFadeImg(wstring filePath);
	void setupTest(wstring filePath);
	void updateOther();
	// ���� �� ���� update
	void updateGameReady();
	void renderOther();
	// ���� �� ���� render
	void renderGameReady();
	// ���� �� ������ ����Ǹ� fade render
	void renderFade();
	void renderTest();

	// �ΰ��� �ε��� ���⼭ ���
	// �����带 ������ �ΰ��� Ŭ�������� �����ؾ� ��
	// ����� ������ �ε� �� ���� ȭ���̶� ���� ��� ���� �ε� ��Ŵ
	void renderIngameLoading();
	void destroyOther();
};


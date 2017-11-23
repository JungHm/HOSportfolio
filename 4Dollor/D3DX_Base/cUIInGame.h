#pragma once
#include "cUIObject.h"

#define SKILLCOUNT 5
#define SKILLCOUNTNUM 10
#define HPMAX 100

struct tagHPBar
{
	float current;
	float max;
	wstring filePath;
	LPDIRECT3DTEXTURE9 texture;
	D3DXMATRIXA16 matWorld;
	D3DXVECTOR3 pos;
	vector<ST_PT_VERTEXT> vertex;
};

class cUIInGame : public cUIObject
{
private:
	// 현재 버튼 클릭으로 씬 넘길 때 사용함.
	SYNTHESIZE(bool, m_GameEnd, GameEnd);

	vector<tagHPBar> m_VHPBar;
	// 미니언은 map으로 만들고 첫번째 인자에 걔들 클래스? 주소값을 넣자
	float m_HPBarSizeX;
	float m_HPBarSizeY;
	float m_HPBarHeight;

public:
	cUIInGame();
	~cUIInGame();

	// 스킬 언락. q = 1, w = 2 순서
	void SetSkillUnlock(int SkillIndex, bool unlock);
	// 스킬 사용 시. q = 1, w = 2 순서
	void SetSkillUse(int SkillIndex, bool used);
	// 스킬 사용 쿨타임 표시
	void SetSkillUseCooldown(int SkillIndex, float count);

	// 순수 가상함수로 실행하는 것들
	void setupOther();
	void updateOther();
	void renderOther();
	int updateButtonOverCallback(int num);
	int updateButtonCallback(int num);

	// 체력바 셋팅
	void setupHpBar(wstring filePath);
	// 체력 비율, matrix scale 계산
	void updateBar(bool pc, D3DXVECTOR3 pt, int currHp);
	// 체력바 랜더
	void renderBar();

	void destroyOther();
};


#pragma once
#include "cUIObject.h"

#define SKILLCOUNT 5
#define SKILLCOUNTNUM 10
#define HPMAX 100
#define FADEINSPEED 10
#define SKILLUNLOCKEFXREPEATCOUNT 10
#define DEADSIDE 2
#define VICTORYRESOURCE 3

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
	bool m_IsVictory;
	vector<tagHPBar> m_VHPBar;
	// 미니언은 map으로 만들고 첫번째 인자에 걔들 클래스? 주소값을 넣자
	float m_HPBarSizeX;
	float m_HPBarSizeY;
	float m_HPBarHeight;

	tagUISpriteEfx m_Fade;
	tagUISpriteEfx m_Dead;
	tagUISpriteEfx m_DeadSide[DEADSIDE];
	tagUISpriteEfx m_SkillUnlockEfx;
	tagUISpriteEfx m_VictoryEfx[VICTORYRESOURCE];
	int m_SkillUnlockEfxAlphaCount;	// 알파값 왔다갔다 반복 몇번
	int m_LvUpCount;
	vector<tagUISpriteButton*> m_SkillUnlock;

public:
	cUIInGame();
	~cUIInGame();

	void setupDeadAdd();
	void SetDead(bool deadEnable);
	void rednerDead();

	void setupDeadSideAdd(bool left);
	void renderDeadSide();

	void setupFadeAdd(wstring filePath);
	void setupSkillLockList();
	void setupSkillUnlockEfx(wstring filePath);

	// 승리 시
	void setupVictoryAdd(wstring filePath, int index, float scale);
	void SetVictory();	// 승리 외 UI는 모두 숨기기 위함
	void renderVictory();

	// 스킬 언락. q = 1, w = 2 순서
	void SetSkillUnlock(int SkillIndex, bool unlock);
	// 스킬 선택해서 언락할 때 언락 가능한 남은 스킬들 위치 정렬
	void skillUnlockPtChange(int index);
	void skillUnlockEfx(int index);
	void updateSkillUnlockEfx();
	void skillChooseList();
	// 스킬 사용 시. q = 1, w = 2 순서
	void SetSkillUse(int SkillIndex, bool used);
	// 스킬 사용 쿨타임 표시
	void SetSkillUseCooldown(int SkillIndex, float count);
	void SetLevelUp();

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
	void renderFade();
	void renderAbilityAddGuide();
	void renderSkillUnlockEfx();
	void destroyOther();

	

	// 레벨업 시 스킬 해방 몇개 할 수 있는지 count 누적.
	void SetLvUpAddCount(int count) { m_LvUpCount += count; }
};


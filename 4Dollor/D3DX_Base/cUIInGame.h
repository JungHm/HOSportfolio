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
	// ���� ��ư Ŭ������ �� �ѱ� �� �����.
	SYNTHESIZE(bool, m_GameEnd, GameEnd);
	bool m_IsVictory;
	vector<tagHPBar> m_VHPBar;
	// �̴Ͼ��� map���� ����� ù��° ���ڿ� �µ� Ŭ����? �ּҰ��� ����
	float m_HPBarSizeX;
	float m_HPBarSizeY;
	float m_HPBarHeight;

	tagUISpriteEfx m_Fade;
	tagUISpriteEfx m_Dead;
	tagUISpriteEfx m_DeadSide[DEADSIDE];
	tagUISpriteEfx m_SkillUnlockEfx;
	tagUISpriteEfx m_VictoryEfx[VICTORYRESOURCE];
	int m_SkillUnlockEfxAlphaCount;	// ���İ� �Դٰ��� �ݺ� ���
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

	// �¸� ��
	void setupVictoryAdd(wstring filePath, int index, float scale);
	void SetVictory();	// �¸� �� UI�� ��� ����� ����
	void renderVictory();

	// ��ų ���. q = 1, w = 2 ����
	void SetSkillUnlock(int SkillIndex, bool unlock);
	// ��ų �����ؼ� ����� �� ��� ������ ���� ��ų�� ��ġ ����
	void skillUnlockPtChange(int index);
	void skillUnlockEfx(int index);
	void updateSkillUnlockEfx();
	void skillChooseList();
	// ��ų ��� ��. q = 1, w = 2 ����
	void SetSkillUse(int SkillIndex, bool used);
	// ��ų ��� ��Ÿ�� ǥ��
	void SetSkillUseCooldown(int SkillIndex, float count);
	void SetLevelUp();

	// ���� �����Լ��� �����ϴ� �͵�
	void setupOther();
	void updateOther();
	void renderOther();
	int updateButtonOverCallback(int num);
	int updateButtonCallback(int num);

	// ü�¹� ����
	void setupHpBar(wstring filePath);
	// ü�� ����, matrix scale ���
	void updateBar(bool pc, D3DXVECTOR3 pt, int currHp);

	// ü�¹� ����
	void renderBar();
	void renderFade();
	void renderAbilityAddGuide();
	void renderSkillUnlockEfx();
	void destroyOther();

	

	// ������ �� ��ų �ع� � �� �� �ִ��� count ����.
	void SetLvUpAddCount(int count) { m_LvUpCount += count; }
};


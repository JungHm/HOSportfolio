#pragma once
#include "cUIObject.h"

#define SKILLCOUNT 5
#define SKILLCOUNTNUM 10
#define HPMAX 100
#define FADEINSPEED 30
#define SKILLUNLOCKEFXREPEATCOUNT 6
#define DEADSIDE 2
#define VICTORYRESOURCE 4
#define VICTORYCYCLESCALE 1
#define SKILLUNLOCKLISTINTERVAL 75

struct tagHPBar
{
	float current;
	float max;
	wstring filePath;
	LPDIRECT3DTEXTURE9 texture;
	D3DXMATRIXA16 matWorld;
	D3DXVECTOR3 pos;
	vector<ST_PT_VERTEXT> vertex;
	bool enable;
	int id;
};

class cUIInGame : public cUIObject
{
private:
	// ���� ��ư Ŭ������ �� �ѱ� �� �����.
	SYNTHESIZE(bool, m_GameEnd, GameEnd);
	bool m_IsVictory;
	vector<tagHPBar> m_VHPBar;
	vector<tagHPBar> m_VHPBarMinion;
	// �̴Ͼ��� map���� ����� ù��° ���ڿ� �µ� Ŭ����? �ּҰ��� ����
	float m_HPBarSizeX;
	float m_HPBarSizeY;
	float m_HPBarHeight;
	float m_HPBarSizeXM;
	float m_HPBarSizeYM;
	float m_HPBarHeightM;

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

	void SetMinionAdd(int id);
	void SetMinionDelete(int id);
	void setupMinionAdd(wstring filePath, int id);

	// �¸� ��
	void setupVictoryAdd(wstring filePath, int index, float scale, D3DXVECTOR3 pt);
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
	void setupHpBar(wstring filePath, int id);
	// ü�� ����, matrix scale ���
	void updateBar(bool pc, D3DXVECTOR3 pt, int currHp);
	void updateBarMinion(int id, D3DXVECTOR3 pt, int currHp);

	// ü�¹� ����
	void renderBar();
	void renderBarMinion();
	void renderFade();
	void renderAbilityAddGuide();
	void renderSkillUnlockEfx();
	void destroyOther();

	

	// ������ �� ��ų �ع� � �� �� �ִ��� count ����.
	void SetLvUpAddCount() { m_LvUpCount += 1; }
};


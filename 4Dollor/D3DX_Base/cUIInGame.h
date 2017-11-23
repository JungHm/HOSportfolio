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
	// ���� ��ư Ŭ������ �� �ѱ� �� �����.
	SYNTHESIZE(bool, m_GameEnd, GameEnd);

	vector<tagHPBar> m_VHPBar;
	// �̴Ͼ��� map���� ����� ù��° ���ڿ� �µ� Ŭ����? �ּҰ��� ����
	float m_HPBarSizeX;
	float m_HPBarSizeY;
	float m_HPBarHeight;

public:
	cUIInGame();
	~cUIInGame();

	

	// ��ų ���. q = 1, w = 2 ����
	void SetSkillUnlock(int SkillIndex, bool unlock);
	// ��ų ��� ��. q = 1, w = 2 ����
	void SetSkillUse(int SkillIndex, bool used);
	// ��ų ��� ��Ÿ�� ǥ��
	void SetSkillUseCooldown(int SkillIndex, float count);

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
};


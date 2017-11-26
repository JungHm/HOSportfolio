#pragma once
#include "cUIObject.h"

#define SKILLCOUNT 5
#define SKILLCOUNTNUM 10
#define HPMAX 100
#define FADEINSPEED 5
#define SKILLUNLOCKEFXREPEATCOUNT 6
#define VICTORYRESOURCE 4
#define VICTORYCYCLESCALE 1
#define VICTORYCYCLESCALESPEED 0.7
#define VICTORYLIGHTSPEED 20
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
	// 현재 버튼 클릭으로 씬 넘길 때 사용함.
	SYNTHESIZE(bool, m_GameEnd, GameEnd);
	bool m_IsVictory;
	vector<tagHPBar> m_VHPBar;
	vector<tagHPBar> m_VHPBarMinion;
	// 미니언은 map으로 만들고 첫번째 인자에 걔들 클래스? 주소값을 넣자
	float m_HPBarSizeX;
	float m_HPBarSizeY;
	float m_HPBarHeight;
	float m_HPBarSizeXM;
	float m_HPBarSizeYM;
	float m_HPBarHeightM;

	tagUISpriteEfx m_Fade;
	tagUISpriteEfx m_FadeBG;
	tagUISpriteEfx m_Dead;
	tagUISpriteEfx m_SkillUnlockEfx;
	tagUISpriteEfx m_VictoryEfx[VICTORYRESOURCE];
	int m_SkillUnlockEfxAlphaCount;	// 알파값 왔다갔다 반복 몇번
	int m_LvUpCount;
	vector<tagUISpriteButton*> m_SkillUnlock;
	int m_DeadCount;

public:
	cUIInGame();
	~cUIInGame();

	// 죽음 연출
	void setupDeadAdd();
	// 외부에서 죽음을 활성화 할 때 사용
	void SetDead(bool deadEnable);
	// 외부에서 죽은 후 부활 카운트 Set
	void SetDeadCount(int second);
	// 죽음 관련 랜더
	void rednerDead();

	// 게임 시작할 때 페이드
	void setupFadeAdd(wstring filePath);
	// 렙업 시 언락할 수 있는 스킬 리스트
	void setupSkillLockList();
	// 스킬 언락 연출 sprite 설정
	void setupSkillUnlockEfx(wstring filePath);

	// 미니언 추가되었을 때 체력바 push_back
	void SetMinionAdd(int id);
	// 미니언 죽었을 때 체력바 erase
	void SetMinionDelete(int id);
	// 미니언 체력바 기본 셋팅
	void setupMinionAdd(wstring filePath, int id);

	// 승리 시 연출할 리소스 등록
	void setupVictoryAdd(wstring filePath, int index, float scale, D3DXVECTOR3 pt);
	// 외부에서 승리 시 Set
	void SetVictory();	// 승리 외 UI는 모두 숨기기 위함
	// 승리 관련 연출 랜더
	void renderVictory();

	// 스킬 언락. q = 1, w = 2 순서
	void SetSkillUnlock(int SkillIndex, bool unlock);
	// 스킬 선택해서 언락할 때 언락 가능한 남은 스킬들 위치 정렬
	void skillUnlockPtChange(int index);
	// 스킬 언락할 때 번쩍이는 육각형
	void skillUnlockEfx(int index);
	// 스킬 언락할 때 번쩍이는 육각형 update
	void updateSkillUnlockEfx();
	// 초상화 선택했을 때 언락할 수 있는 스킬이 있다면 리스트 출력.
	void skillChooseList();
	// 스킬 사용 시. q = 1, w = 2 순서
	void SetSkillUse(int SkillIndex, bool used);
	// 스킬 사용 쿨타임 표시
	void SetSkillUseCooldown(int SkillIndex, float count);
	// 외부에서 렙업 시 Set
	void SetLevelUp(int level);

	// 순수 가상함수로 실행하는 것들
	void setupOther();
	void updateOther();
	void renderOther();
	int updateButtonOverCallback(int num);
	int updateButtonCallback(int num);

	// 체력바 셋팅
	void setupHpBar(wstring filePath, int id);
	// 체력 비율, matrix scale 계산
	void updateBar(bool pc, D3DXVECTOR3 pt, int currHp);
	// 미니언 체력바
	void updateBarMinion(int id, D3DXVECTOR3 pt, int currHp);

	// 체력바 랜더
	void renderBar();
	void renderBarMinion();
	// 페이즈 관련 랜더
	void renderFade();
	// 언락할 수 있는 스킬이 있을 때 안내해주는 화살표 랜더
	void renderAbilityAddGuide();
	// 스킬 언락 후 스킬 아이콘이 반짝이는 연출 랜더
	void renderSkillUnlockEfx();
	void destroyOther();

	

	// 레벨업 시 스킬 해방 몇개 할 수 있는지 count 누적. 스킬포인트 개념
	void SetLvUpAddCount() { m_LvUpCount += 1; }
};


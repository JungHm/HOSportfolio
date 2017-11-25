#pragma once

enum TEAM
{
	TEAM_BLUE,         // 팀은 크게 파란팀(아군), 빨간팀(적군)으로 나뉨
	TEAM_RED           // 중립몬스터 추가 시, enum문에 추가
};

enum TOWER_STATE
{
	NONE, FIRE
};

typedef struct tagTower
{
	D3DXMATRIXA16   matWorld;
	D3DXMATRIXA16   matScal;
	D3DXMATRIXA16   matRotY;
	D3DXMATRIXA16   matTrans;
	D3DXVECTOR3		vPosition;
	D3DXVECTOR3		vDirection;
	TOWER_STATE		eState;
	wstring			sPath;
	DWORD			dAttack;
	DWORD			dNone;
	float			fBlendTime;
	float			fPassedBlendTime;
	float			fAngleY;
	int				nKey;
	bool			isFind;
	ST_SPHERE		sSphere;
}TOWER;

class cTower
{
private:
	TOWER m_sTower[2];

public:
	cTower();
	~cTower();

	void Setup(IN D3DXVECTOR3 vBTowerPos, IN D3DXVECTOR3 vRTowerPos);
	void Update();
	void Render();
	void BlueFindEnemy(ST_SPHERE sSphere);
	void RedFindEnemy(ST_SPHERE sSphere);
};


#pragma once

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

	TOWER GetTower(int nIndex) { return m_sTower[nIndex]; }
	void Setup(IN D3DXVECTOR3 vBTowerPos, IN D3DXVECTOR3 vRTowerPos);
	void Update();
	void Render();
	void BlueFindEnemy(ST_SPHERE sSphere);
	void RedFindEnemy(ST_SPHERE sSphere);
	D3DXVECTOR3 GetTowerPos(int team) { return m_sTower[team].vPosition; }
	int GetTowerHP(int team) { return 20; }	// 타워 체력 추가 후 작업
};


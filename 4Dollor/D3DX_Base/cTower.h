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

	void Setup(IN D3DXVECTOR3 vBTowerPos, IN D3DXVECTOR3 vRTowerPos);
	void Update();
	void Render();
	void BlueFindEnemy(ST_SPHERE sSphere);
	void RedFindEnemy(ST_SPHERE sSphere);

	// 두점 사이의 거리
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}
};


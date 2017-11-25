#pragma once

#define g_Effect cFireEffect::GetInstance()

enum EKIND
{
	TOWER_FIRE, 
	TARGET_HIT
};

struct tagEffect
{
	vector<ST_PC_VERTEXT> vecParticle;
	D3DXMATRIXA16         matTowerWorld;
	D3DXMATRIXA16		  matWorld;
	D3DXMATRIXA16		  matRotY;
	D3DXMATRIXA16         matTrans;
	D3DXVECTOR3			  vPosition;
	EKIND				  eKind;
	float				  fAngleY;
	char*				  pFullPath;
	int					  nRndNUm;
};

class cFireEffect
{
	SINGLETONE(cFireEffect);

private:
	vector<tagEffect> m_vecEffect;
	SYNTHESIZE(D3DXVECTOR3, m_vEnemyPos, EnemyPos);
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_vTowerWorld, TowerWorld);
 
public:
	void CreatEffect(
		IN char* pFullPath,
		IN EKIND eKind,
		IN int nSize,
		IN int nRndNum,
		IN D3DXMATRIXA16* matTowerWorld,
		IN D3DXVECTOR3 vPos,
		IN float fAngleY);

	void Update();
	void Render();
};
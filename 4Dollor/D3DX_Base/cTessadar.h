#pragma once
#include "cCharacter.h"

class cTessadar : public cCharacter
{
private:
	enum CharState
	{
		ATTACK,
		SPELL_Q,
		SPELL_W,
		SPELL_E,
		SPELL_R,
		STAND,
		WALK,

	};
	wstring						m_sPath = wstring(L"Tassadar/Tassadar.X");

	/*LPD3DXMESH					m_pMesh;*/
	float						m_ft;

	D3DXMATRIXA16 matT, matR;
	D3DXVECTOR3 vPos, vDir;

	DWORD dwCurr, dwNew;

	double m_dTimeCurrent;

	float	m_fBlendTime;
	float	m_fPassedBlendTime;

	DWORD dwAttack, dwSpell, dwWalk, dwStand;

	//SYNTHESIZE(int, m_State, State);

	int xKey;


public:
	MATRIX16_FIX;
	cTessadar();
	~cTessadar();
	virtual void AnimSetUp() override;
	virtual void SetUp()override;
	virtual void Update()override;
	virtual void Render(D3DXMATRIXA16& matRT)override;
	virtual void ChangeAni()override;
	virtual void BlendAni(int State)override;
};

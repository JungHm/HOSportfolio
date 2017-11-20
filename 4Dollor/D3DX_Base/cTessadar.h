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

private:
	std::vector<ST_PT_VERTEXT> vecRange;
	std::vector<ST_PT_VERTEXT> vecHit;
	std::vector<ST_PT_VERTEXT> vecBarrier;
	LPDIRECT3DTEXTURE9	rangeTexture;
	LPDIRECT3DTEXTURE9	hitTexture;
	LPDIRECT3DTEXTURE9 BarrierTex;
	//Skill coolDown
	
	//W, E 지속시간
	float keepTime;
	float fTime;
	bool SkillW;
	bool SkillE;
public:
	MATRIX16_FIX;
	cTessadar();
	~cTessadar();
	//xfile 에서 가져온 애니메이션 인덱스를 저장
	virtual void AnimSetUp() override;
	virtual void SetUp()override;
	virtual void Update()override;
	virtual void Render(D3DXMATRIXA16& matR, D3DXMATRIXA16& matT)override;
	//애니메이션 바뀔때 아 이거 잘 모루게쒀여 블렌두 배우고 나니까 음.. 어.. 블렌드 배우기 전까지 이거 쒔는뒈 블렌드 추가하고나서 좀 이상훼여 빼면 안뒈드라구요 귀찮아서 수정안하고 쓰고있어요
	virtual void ChangeAni()override;
	//애니메이션 블렌딩
	virtual void BlendAni(int State)override;

	void SkillUiVertex();
};


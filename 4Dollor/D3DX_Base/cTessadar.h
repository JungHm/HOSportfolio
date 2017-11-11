#pragma once
class cTessadar
{
private:
	enum CharState
	{
		ATTACK,
		SPELL,
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

	DWORD dwAttack, dwSpell, dwWalk, dwStand;

	int m_State;
	int xKey;
public:
	cTessadar();
	~cTessadar();

	void AnimSetUp();
	void SetUp();
	void Update();
	void Render();

	void ChangeAni();

};


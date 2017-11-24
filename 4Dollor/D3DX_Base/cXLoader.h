#pragma once
using namespace std;
class cAllocateHierarchy;

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


class cXLoader
{

private:	
	LPD3DXFRAME					m_pFrameRoot;
	LPD3DXANIMATIONCONTROLLER	m_pAnimControl;
	wstring						m_sPath = wstring(L"Tassadar/Tassadar.X");
	bool ShaderSet;
public:
	MATRIX16_FIX;
	cXLoader();
	~cXLoader();
	// OBB
	SYNTHESIZE(D3DXVECTOR3, m_vMin, Min);
	SYNTHESIZE(D3DXVECTOR3, m_vMax, Max);
	//xfile 로드 하는겁니다
	void XfileLoad(IN wstring m_sPath);
	void Update();
	void Render(D3DXMATRIXA16& matRT);

	void SetupBoneMatrixPtrs(D3DXFRAME* pFrame);
	void UpdateSkinnedMesh(D3DXFRAME* pFrame);
	void RecursiveFrameRender(D3DXFRAME* pParent, D3DXMATRIXA16* pParentWorldTM, D3DXMATRIXA16& matRT);


public:
	LPD3DXANIMATIONCONTROLLER getAnimCtrl() { return m_pAnimControl; }

};


#pragma once
using namespace std;
class cAllocateHierarchy;

enum CharState
{
	ATTACK,
	SPELL,
	STAND,
	WALK,
};


class cXLoader
{
private:
	LPD3DXMESH m_pMesh; //Mesh 객체
	D3DMATERIAL9* m_pMtl; //Mesh에서 사용할 재질.
	LPDIRECT3DTEXTURE9* m_pTexture;//Mesh에서 사용할 텍스쳐.
	DWORD m_NumMtl;//Mesh에서 사용중인 재질의 개수.

	cAllocateHierarchy* m_pAlloc;
	LPD3DXFRAME					m_pFrameRoot;
	wstring						m_sPath = wstring(L"Tassadar/Tassadar.X");
	LPD3DXANIMATIONCONTROLLER	m_pAnimControl;

	/*LPD3DXMESH					m_pMesh;*/
	float						m_ft;

	D3DXMATRIXA16 matT, matR;
	D3DXVECTOR3 vPos, vDir;

	DWORD dwCurr, dwNew;

	double m_dTimeCurrent;

	DWORD dwAttack, dwSpell, dwWalk, dwStand;//, dwSelect;

	int m_State;

public:
	cXLoader();
	HRESULT InitGeometry();
	void SetUp();
	void Update();
	void Render();

	void SetupWorldMatrix(D3DXFRAME* pFrame, D3DXMATRIXA16* pmatParent);
	void SetupBoneMatrixPtrs(D3DXFRAME* pFrame);
	void UpdateSkinnedMesh(D3DXFRAME* pFrame);
	void RecursiveFrameRender(D3DXFRAME* pParent, D3DXMATRIXA16* pParentWorldTM);

	~cXLoader();
};


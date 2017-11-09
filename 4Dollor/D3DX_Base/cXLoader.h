#pragma once
using namespace std;
class cAllocateHierarchy;

enum CharState
{
	IDLE,
	FIRE,
	FIREPOST,
	SELECT,
	RELOAD
};


class cXLoader
{
private:
	LPD3DXMESH m_pMesh; //Mesh ��ü
	D3DMATERIAL9* m_pMtl; //Mesh���� ����� ����.
	LPDIRECT3DTEXTURE9* m_pTexture;//Mesh���� ����� �ؽ���.
	DWORD m_NumMtl;//Mesh���� ������� ������ ����.

	cAllocateHierarchy* m_pAlloc;
	LPD3DXFRAME					m_pFrameRoot;
	LPD3DXFRAME					m_pFrameRootOrigin;
	wstring						m_sPath = wstring(L"Zealot/zealot.X");
	LPD3DXANIMATIONCONTROLLER	m_pAnimControl;

	/*LPD3DXMESH					m_pMesh;*/
	LPD3DXBUFFER				m_pBuffer;
	vector<LPDIRECT3DTEXTURE9>	m_vecTexture;
	float						m_ft;

	D3DXMATRIXA16 matT, matR;
	D3DXVECTOR3 vPos, vDir;

	DWORD dwCurr, dwNew;

	double m_dTimeCurrent;

	DWORD dwFire, dwReload, dwIdle, dwFirePost, dwSelect;

	CharState m_State;

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


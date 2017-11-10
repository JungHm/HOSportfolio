#pragma once
class cTessadar
{
private:
	LPD3DXMESH m_pMesh; //Mesh ��ü
	D3DMATERIAL9* m_pMtl; //Mesh���� ����� ����.
	LPDIRECT3DTEXTURE9* m_pTexture;//Mesh���� ����� �ؽ���.
	DWORD m_NumMtl;//Mesh���� ������� ������ ����.

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
	cTessadar();
	~cTessadar();
};


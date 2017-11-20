#pragma once
class cGrid
{
private:
	vector<ST_PNT_VERTEXT>  m_vecVertex;	// ���ؽ�
	vector<DWORD>			m_vecIndex;		// �ε���
	vector<ST_PC_VERTEXT>	m_vecAxis;		// �� ���ؽ�
	LPD3DXMESH				m_pMesh;		// �Ž�
	D3DMATERIAL9			m_mtl;			// ���͸���
	LPDIRECT3DTEXTURE9		m_pTexTure;		// �ؽ�ó
	D3DXMATRIXA16			m_matWorld;		// �׸��� ����

	int   m_nRow;			// �� ����
	int   m_nCol;			// �� ����
	int   m_nTotalVertex;	// �� ������ ����
	int	  m_nTotalIndex;	// �� �ε��� ����
	float m_fTileSize;		// �׸��� ����(ũ��)
	float m_fStartPosX;		// �׸��� ���� ���� x��ǥ
	float m_fStartPosZ;		// �׸��� ���� ���� z��ǥ

private:
	GETTER(vector<ST_PC_VERTEXT>, m_vecPicVertex, PicVertex); // ��ŷ�� ���ؽ�

public:
	MATRIX16_FIX;
	cGrid();
	~cGrid();

	// �ʱ�ȭ
	void Setup(IN char* szFolder, IN char* szFile, IN int nRow, IN int nCol, IN float fSize);
	// ����
	void Render();
};


#pragma once

class cObjLoader;

class cSaveLoad
{
private:
	cObjLoader*					m_pObjLoader;		 // ������Ʈ �δ� Ŭ����
	vector<OBJECT>				m_vecFieldObj;		 // �ʵ忡 ��ġ�Ǵ� ������Ʈ
	string						m_sFileName[OBJNUM]; // ���� �̸�
	LPD3DXMESH					m_pObjMesh[OBJNUM];	 // �ε��� �Ž��� �������� �������� 
	map<int, vector<cMtlTex*>>	m_mapObjMtlTex;		 // �Ž��� ���׸���, �ؽ��ĸ� ���� ���� �� ���� ��

public:
	cSaveLoad();
	~cSaveLoad();

	// ���� �� ������ �̸� Get
	string GetFileName(int nIndex) { return m_sFileName[nIndex]; }
	// �δ� �� �Ž� Get
	LPD3DXMESH GetObjMesh(int nIndex) { return m_pObjMesh[nIndex]; }
	// ���� �� ���͸���, �ؽ�ó ���� Get
	vector<cMtlTex*> GetMapObjMtltex(int nkey) { return m_mapObjMtlTex[nkey]; }
	// �ʵ忡 ��ġ�Ǵ� ������Ʈ ���� �Լ�
	void CreateObj(IN int nKind, IN LPD3DXMESH pMesh, IN vector<cMtlTex*> vecValue, IN string sFileName, IN D3DXVECTOR3 vScal, IN D3DXVECTOR3 vPos, IN float fAngleY);
	// ��ġ �� �������� ����
	void CreateObjRender();
	// ������Ʈ �ڿ��� �ϳ��� ����
	void RemoveObj();
	// ������Ʈ ���̺�
	void SaveFieldObj();
	// ������Ʈ �δ�
	void LoadFieldObj();
};


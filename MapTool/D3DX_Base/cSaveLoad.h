#pragma once

class cObjLoader;

class cSaveLoad
{
private:
	cObjLoader*					m_pObjLoader;		 // ������Ʈ �δ� Ŭ����
	LPD3DXMESH					m_pObjMesh[OBJNUM];	 // �ε��� �Ž��� �������� �������� 
	string						m_sFileName[OBJNUM]; // ���� �̸�
	map<int, vector<cMtlTex*>>	m_mapObjMtlTex;		 // �Ž��� ���׸���, �ؽ��ĸ� ���� ���� �� ���� ��
	D3DMATERIAL9				m_mtlNone;			 // ���� �����ʾ��� �� ��� ���͸���
	D3DMATERIAL9				m_mtlSelected;		 // ���� �Ǿ��� �� ��� ���͸���
	vector<OBJECT>				m_vecFieldObj;		 // �ʵ忡 ��ġ�Ǵ� ������Ʈ
	vector<ST_BOX>				m_vecFieldBox;		 // �ʵ忡 ��ġ�Ǵ� �浹 �ڽ�
	SYNTHESIZE_PASS_BY_REF(vector<ST_SPHERE>, m_vecFieldNodeSphere, FieldNodeSphere); // �ʵ忡 ��ġ�Ǵ� ���ͽ�Ʈ�� ��� �����
	SYNTHESIZE_PASS_BY_REF(vector<ST_COST>, m_vecCost, Cost);	// ���� ��
	SYNTHESIZE_PASS_BY_REF(vector<ST_PC_VERTEXT>, m_vecNodeLine, NodeLinde); // �� ������ ���� ����
	
public:
	cSaveLoad();
	~cSaveLoad();

	// ���� �� ������ �̸� Get
	string GetFileName(int nIndex) { return m_sFileName[nIndex]; }
	// �δ� �� �Ž� Get
	LPD3DXMESH GetObjMesh(int nIndex) { return m_pObjMesh[nIndex]; }
	// ���� �� ���͸���, �ؽ�ó ���� Get
	vector<cMtlTex*> GetMapObjMtltex(int nkey) { return m_mapObjMtlTex[nkey]; }
	// �ʵ忡 ��ġ�� ������Ʈ ���� Get
	int GetFieldObjNum() { return m_vecFieldObj.size(); }
	// �ʵ忡 ��ġ�Ǵ� �浹�ڽ� ���� �Լ�
	void CreateBox(IN LPD3DXMESH pMesh, IN D3DXVECTOR3 vScal, IN D3DXVECTOR3 vPos, IN float fAngleY);
	// �ʵ忡 ��ġ�Ǵ� ������Ʈ ���� �Լ�
	void CreateObj(IN int nKind, IN LPD3DXMESH pMesh, IN vector<cMtlTex*> vecValue, IN string sFileName, IN D3DXVECTOR3 vScal, IN D3DXVECTOR3 vPos, IN float fAngleY);
	// �ʵ忡 ��ġ�Ǵ� ���ͽ�Ʈ�� ��� ���� �Լ�
	void CreateNodeSphere(IN LPD3DXMESH pMesh, IN D3DXVECTOR3 vPos, IN vector<NODE> vecNode);
	// ��ġ �� ������Ʈ ����
	void CreateObjRender();
	// ������Ʈ �ڿ��� �ϳ��� ����
	void RemoveObj();
	// ������Ʈ ���̺�
	void SaveFieldObj();
	// ������Ʈ �δ�
	void LoadFieldObj();
};
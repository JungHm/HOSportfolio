#pragma once

class cObjLoader;

class cSaveLoad
{
private:
	cObjLoader*					m_pObjLoader;				// ������Ʈ �δ� Ŭ����
	LPD3DXMESH					m_pObjMesh[OBJNUM];			// �ε��� �Ž��� �������� �������� 
	string						m_sFileName[OBJNUM];		// ���� �̸�
	map<int, vector<cMtlTex*>>	m_mapObjMtlTex;				// �Ž��� ���׸���, �ؽ��ĸ� ���� ���� �� ���� ��
	D3DMATERIAL9				m_mtlNone;					// ���� �����ʾ��� �� ��� ���͸���
	D3DMATERIAL9				m_mtlSelected;				// ���� �Ǿ��� �� ��� ���͸���
	SYNTHESIZE(vector<OBJECT>, m_vecFieldObj, FieldObj);	// �ʵ忡 ��ġ�Ǵ� ������Ʈ
	SYNTHESIZE(vector<ST_BOX>, m_vecFieldBox, FielBox);		// �ʵ忡 ��ġ�Ǵ� �浹 �ڽ�
	SYNTHESIZE(vector<ST_COST>, m_vecCost, Cost);			// ���ͽ�Ʈ�� ��ã�� ���� ��
	SYNTHESIZE_PASS_BY_REF(vector<ST_SPHERE_NODE>, m_vecFieldNodeSphere, FieldNodeSphere); // �ʵ忡 ��ġ�Ǵ� ���ͽ�Ʈ�� ��� �����
	SYNTHESIZE_PASS_BY_REF(vector<ST_PC_VERTEXT>, m_vecNodeLine, NodeLinde);			   // �� ������ ���� ����
	
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
	// ���ͽ�Ʈ�� ��� ���Ű� �ʱ�ȭ
	void CostSetup(IN int nSize);
	// ��ġ �� ������Ʈ ����
	void CreateObjRender();
	// ������Ʈ �ڿ��� �ϳ��� ����
	void RemoveObj();
	// �浹 �ڽ� �ڿ��� �ϳ��� ����
	void RemoveBox();
	// ��� �ڿ��� �ϳ��� ����, ������� �� 2���� ����
	void RemoveNode();
	// ������Ʈ, �浹�ڽ�, ���, ��� ������� ���̺�
	void SaveFieldObj();
	// ������Ʈ, �浹�ڽ�, ���, ��� ���¶��� �δ�
	void LoadFieldObj();
};
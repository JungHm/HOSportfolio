#pragma once

class cGrid;
class cInfomation;
class cObjLoader;
class cMtlTex;
class cSaveLoad;

class cMapTool
{
private:
	cGrid*						m_pGrid;
	cInfomation*				m_pInfo;
	cObjLoader*					m_pObjLoader;
	cSaveLoad*					m_pSaveLoad;
	map<int, vector<cMtlTex*>>	m_mapObjMtlTex;

private:
	OBJECT		m_sObj;				  // ���� ���콺�� �����̴� ������Ʈ ����
	LPD3DXMESH	m_pObjMesh[OBJNUM];	  // �ε��� �Ž��� �������� �������� 
	int			m_nIndex;			  // �������� ������Ʈ�� �ε���
	bool		m_isPicking;		  // ��ŷ ���� ����
	bool		m_isAllocate;		  // ��ġ ����
	string		m_sFileName[OBJNUM];  // ���� �̸�

public:
	cMapTool();
	~cMapTool();

	void Setup();
	void Update();
	void Render();

	void SetUpObj();
	void ObjPicking(IN UINT message, IN WPARAM wParam, IN LPARAM lParam);
	void ObjSelect();
};


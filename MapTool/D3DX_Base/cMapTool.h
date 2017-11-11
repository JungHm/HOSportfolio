#pragma once

class cGrid;
class cInfomation;
class cObjLoader;
class cMtlTex;

class cMapTool
{
private:
	cGrid*			m_pGrid;
	cInfomation*	m_pInfo;
	cObjLoader*		m_pObjLoader;
	map<int, vector<cMtlTex*>>	 m_mapObjMtlTex;

private:
	OBJECT		m_sObj;
	LPD3DXMESH	m_pObjMesh[OBJNUM];	  // �Ž��� ����
	int			m_nIndex;			  // �ε���
	bool		m_isPicking;		  // ��ŷ ���� ����
	bool		m_isAllocate;		  // ��ġ ����

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


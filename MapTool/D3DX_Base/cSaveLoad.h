#pragma once

class cSaveLoad
{
private:
	vector<OBJECT>	m_vecFieldObj;	  // �ʵ忡 ��ġ�Ǵ� ������Ʈ

public:
	cSaveLoad();
	~cSaveLoad();

	void CreateObj(IN LPD3DXMESH pMesh, IN vector<cMtlTex*> vecValue, IN string sFileName, IN D3DXVECTOR3 vScal, IN D3DXVECTOR3 vPos, IN float fAngleY);

	void CreateObjRender();

	void Save();
};


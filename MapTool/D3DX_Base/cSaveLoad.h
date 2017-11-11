#pragma once

class cSaveLoad
{
private:
	vector<OBJECT>	m_vecFieldObj;	  // 필드에 배치되는 오브젝트

public:
	cSaveLoad();
	~cSaveLoad();

	void CreateObj(IN LPD3DXMESH pMesh, IN vector<cMtlTex*> vecValue, IN string sFileName, IN D3DXVECTOR3 vScal, IN D3DXVECTOR3 vPos, IN float fAngleY);

	void CreateObjRender();

	void Save();
};


#pragma once
class cCube;
class iMap;

class cCubeMan : public cGameObject
{
private:
	cCube* m_pRoot;

	D3DXMATRIXA16				m_matWorld;
	float						m_fRotY;

	LPDIRECT3DTEXTURE9			m_pTexture;
	D3DMATERIAL9				m_stMtl;

	SYNTHESIZE(cAction*, m_pAction, Action);

	iMap*						m_pMap;

public:
	cCubeMan();
	~cCubeMan();

	void Setup();
	void Update(iMap* pMap);
	void Render();
	void SetMaterial();

	virtual void OnActionFinish(cAction* pSender) override;
};


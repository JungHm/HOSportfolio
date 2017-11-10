#pragma once
#include "iScene.h"

class cGrid;
class cCamera;
class cXLoader;

class cMainMenu : public iScene
{
private:
	std::vector<ST_PC_VERTEXT>	m_vecVertex;
	cGrid*		m_pGrid;
	cCamera*	m_pCamera;
	
	cXLoader*		m_pAba;

	LPDIRECT3DTEXTURE9		m_pD3DTexture;
public:
	cMainMenu();
	~cMainMenu();

	virtual void SetUp() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;

	void SetLight();

};


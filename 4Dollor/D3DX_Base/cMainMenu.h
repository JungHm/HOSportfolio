#pragma once
#include "iScene.h"

class cGrid;
class cCamera;
class cTessadar;

class cMainMenu : public iScene
{
private:
	std::vector<ST_PC_VERTEXT>	m_vecVertex;
	cGrid*		m_pGrid;
	cCamera*	m_pCamera;
	cTessadar*	m_pTessadar;

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


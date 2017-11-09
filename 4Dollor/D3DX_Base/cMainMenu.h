#pragma once
#include "iScene.h"

class cGrid;
class cCamera;
class cObjLoader;
class cGroup;
class cObjMap;
class cXLoader;

class cMainMenu : public iScene
{
private:
	std::vector<ST_PC_VERTEXT>	m_vecVertex;
	cGrid*		m_pGrid;
	cCamera*	m_pCamera;
	cObjLoader*		m_pObjLoader;
	
	cXLoader*		m_pAba;

	std::vector<cGroup*>	m_vecGroup;
	std::vector<ST_PT_VERTEXT>	m_vecTriVertex;

	LPDIRECT3DTEXTURE9		m_pD3DTexture;
	LPDIRECT3DTEXTURE9		m_pD3DTexture1;
	LPD3DXFONT				m_pFont;
public:
	cMainMenu();
	~cMainMenu();

	virtual void SetUp() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;

	void RenderObjFile();
	void SetLight();

};


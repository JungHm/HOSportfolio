#pragma once
#include "iScene.h"

class cGrid;
class cCamera;
class cObjLoader;
class cGroup;
class cObjMap;
class cAseNode;
class cUIMainMenu;
class cUILoadingClientBegin;


class cMainMenu : public iScene
{
private:
	std::vector<ST_PC_VERTEXT>	m_vecVertex;
	cGrid*		m_pGrid;
	cCamera*	m_pCamera;
	cObjLoader*		m_pObjLoader;
	cObjMap*		m_pObjMap;
	//cAseNode*		m_pRootNode;
	cUIMainMenu*	m_UI;
	cUILoadingClientBegin* m_UILoading;

	std::vector<cGroup*>	m_vecGroup;
	std::vector<ST_PT_VERTEXT>	m_vecTriVertex;
	std::vector<ST_PNT_VERTEXT>	m_vecFbxVertex;
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

	void LoadSurface();
};


#pragma once

class cAseNode;
class cMtlTex;

class cAseLoader
{
private:
	FILE*	m_fp;
	char	m_szToken[1024];
	std::map<std::string, cAseNode*>	m_mapNode;
	std::vector<cMtlTex*>				m_vecMtlTex;

public:
	cAseLoader();
	~cAseLoader();

	cAseNode* Load(char* szFullPath);

private:
	char*	GetToken();
	int		GetInteger();
	float	GetFloat();
	bool	IsWhite(IN char c);
	bool	IsEqual(IN char* str1, IN char* str2);

	void		ProcessSCENE();
	void		ProcessMATERIAL_LIST();
	void		ProcessMATERIAL(OUT cMtlTex* pMtlTex);
	void		ProcessMAP_DIFFUSE(OUT cMtlTex* pMtlTex);
	cAseNode*	ProcessGEOMOBJECT();
	void		ProcessMESH(OUT cAseNode* pNode);
	void		ProcessMESH_VERTEX_LIST(
		OUT std::vector<D3DXVECTOR3>& vecV);
	void		ProcessMESH_FACE_LIST(
		OUT std::vector<ST_PNT_VERTEXT>& vecVertex,
		IN std::vector<D3DXVECTOR3> vecV);
	void		ProcessMESH_NORMALS(
		OUT std::vector<ST_PNT_VERTEXT>& vecVertex);
	void		ProcessMESH_TVERTLIST(OUT std::vector<D3DXVECTOR2>& vecVT);
	void		ProcessMESH_TFACELIST(OUT std::vector<ST_PNT_VERTEXT>& vecVertex,
		IN std::vector<D3DXVECTOR2> vecVT);

	// animation
	void		ProcessNODE_TM(OUT cAseNode* pNode);
	void		ProcessTM_ANIMATION(OUT cAseNode* pNode);
	void		ProcessCONTROL_ROT_TRACK(OUT cAseNode* pNode);
	void		ProcessCONTROL_POS_TRACK(OUT cAseNode* pNode);

	void		SetSceneFrame(OUT cAseNode* pRoot);

	DWORD	m_dwFirstFrame;
	DWORD	m_dwLastFrame;
	DWORD	m_dwFrameSpeed;
	DWORD	m_dwTicksPerFrame;

};


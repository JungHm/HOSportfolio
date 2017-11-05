#pragma once
#include "cObject.h"
#include "cMtlTex.h"

class cAseNode : public cObject
{
private:
	std::vector<cAseNode*>		m_vecChild;
	SYNTHESIZE_PASS_BY_REF(std::vector<ST_PNT_VERTEXT>, m_vecVertex, Vertex);
	SYNTHESIZE_ADD_REF(cMtlTex*, m_pMtlTex, MtlTex);


	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matLocalTM, LocalTM);
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matWorldTM, WorldTM);
	SYNTHESIZE_PASS_BY_REF(std::vector<ST_POS_SAMPLE>, m_vecPosTrack, PosTrack);
	SYNTHESIZE_PASS_BY_REF(std::vector<ST_ROT_SAMPLE>, m_vecRotTrack, RotTrack);

	int	m_nNumTri;
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
//
//protected: cMtlTex* m_pMtlTex;
//public: virtual cMtlTex* GetMtlTex(void) const { return m_pMtlTex; }
//	public: virtual void SetMtlTex(cMtlTex* var) {
//		if (m_pMtlTex != var) {
//			SAFE_ADD_REF(var);
//			SAFE_RELEASE(m_pMtlTex);
//			m_pMtlTex = var;
//		}
//	}

public:
	cAseNode();
	~cAseNode();

	void AddChild(cAseNode* pChild);
	void Update(int nKeyFrame, D3DXMATRIXA16* pMatParent);
	void Render();
	void Destroy();

	void CalcOriginLocalTM(D3DXMATRIXA16* pMatParent);
	void CalcLoaclRotation(int nKeyFrame, D3DXMATRIXA16& matR);
	void CalcLoaclTranslation(int nKeyFrame, D3DXMATRIXA16& matT);

	void BuildVB(std::vector<ST_PNT_VERTEXT>& vecVertex);

	DWORD	m_dwFirstFrame;
	DWORD	m_dwLastFrame;
	DWORD	m_dwFrameSpeed;
	DWORD	m_dwTicksPerFrame;

	int		GetKeyFrame();
};


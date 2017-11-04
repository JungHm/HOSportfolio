#pragma once
#include "cObject.h"
#include "cMtlTex.h"

struct CTRL_POS
{
	DWORD frame;
	D3DXVECTOR3 pos;
};
struct CTRL_ROT
{
	DWORD frame;
	D3DXQUATERNION rot;
};

class cAseNode : public cObject
{
public:

private:
	std::vector<cAseNode*>		m_vecChild;
	//D3DXMATRIXA16 matLocalTM;
	SYNTHESIZE_PASS_BY_REF(std::vector<ST_PNT_VERTEXT>, m_vecVertex, Vertex);
	SYNTHESIZE_ADD_REF(cMtlTex*, m_pMtlTex, MtlTex);

	SYNTHESIZE_PASS_BY_REF(cAseNode*, pNode, parentNode);
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matLocalTM, LocalTM);
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matWorldTM, WorldTM);
	SYNTHESIZE_PASS_BY_REF(std::vector<CTRL_POS>, m_vecPosTrack, PosTrack);
	SYNTHESIZE_PASS_BY_REF(std::vector<CTRL_ROT>, m_vecRotTrack, RotTrack);
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
private:
	void CalcLoaclRotation(int nKeyFrame, OUT D3DXMATRIXA16& matR);
	void CalcLoaclTranslation(int nKeyFrame, OUT D3DXMATRIXA16& matT);

public:
	cAseNode();
	~cAseNode();

	void AddChild(cAseNode* pChild);
	void Update(int nKeyFrame, D3DXMATRIXA16* pMatParent);
	void Render();
	void Destroy();

	void CalcOriginLocalTM(D3DXMATRIXA16* pMatParent);

	DWORD	m_dwFirstFrame;
	DWORD	m_dwLastFrame;
	DWORD	m_dwFrameSpeed;
	DWORD	m_dwTicksPerFrame;

	int		GetKeyFrame();
};

